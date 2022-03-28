This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

## Notes

1. "DBUS" or "D-bus" = Desktop Bus
    1. https://en.wikipedia.org/wiki/D-Bus
1. "sdbus" or "sd-bus" = systemd implementation of D-bus
1. "IPC" = Inter-Process Communication mechanism
1. "IIO" = Industrial Input/Output
1. `systemd-by-example` is a sub-repo (git submodule).
    1. See the [main readme](../README.md) under the section titled "[How to clone this repo and all git submodules](../README.md#how-to-clone-this-repo-and-all-git-submodules)".


## To generate the PDF book in the `systemd-by-example` dir

```bash
sudo apt update
sudo apt install pandoc
pip3 install MarkdownPP
sudo apt install texlive-xetex

cd path/to/here
cd systemd-by-example
./make_book.sh
# You'll now have "book.pdf" inside directory "systemd-by-example"!
```

References:
1. https://github.com/jreese/markdown-pp - instructions to install MarkdownPP
1. https://tex.stackexchange.com/a/179811/168682 - instructions to install `texlive-xetex`
1. My answer where I added the above info: [Stack Overflow: pandoc: xelatex not found. xelatex is needed for pdf output](https://stackoverflow.com/a/71609094/4561887)

I originally found the [`systemd-by-example` repo](https://gitlab.com/franks_reich/systemd-by-example) by Frank Krick by doing a [Google search for "sdbus example in c"](https://www.google.com/search?q=sdbus+example+in+c&oq=sdbus+example+in+c&aqs=chrome..69i57.224j0j9&sourceid=chrome&ie=UTF-8). It was a few links down.


## `systemd` folder

The `systemd` folder here is a symlink to the `systemd` repo which you must store at the same file level as the eRCaGuy_hello_world repo itself. This is in lieu of adding `systemd` as a "git submodule", because, quite frankly, "git submodules" are a pain and should only be used when you are actively developing the main repo and the sub-repos. I'm not actively developing `systemd`--I just want it as a reference is all. So, let's symlink it!

To actually populate the `systemd` pointed-to dir, do this:

```bash
cd path/to/eRCaGuy_hello_world
# go up one level to be at the same level as the eRCaGuy_hello_world repo
cd .. 
git clone https://github.com/systemd/systemd.git
```

That's it! 

Here is the systemd repo: https://github.com/systemd/systemd
