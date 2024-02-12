<!--
GS
Feb. 2024

MY ANSWER: https://askubuntu.com/a/1502796/327339
-->

> I downloaded `doxygen-1.8.20.linux.bin.tar.gz` here: https://www.doxygen.nl/download.html.
>
> How to install it on Ubuntu


## Download and install the latest version of `doxygen`

For _any_ version of Ubuntu: 

_Tested on Ubuntu 22.04._

Download the latest version here: https://www.doxygen.nl/download.html

...or an older version or the latest version from the official GitHub releases page here: https://github.com/doxygen/doxygen/releases

Extract the `.tar.gz` file, make it and install it. Assuming the version you want is `doxygen-1.10.0.linux.bin.tar.gz`, the full download, make and install instructions would look like this:

```bash
# Create a directory where you want to download it
mkdir -p ~/Downloads/Install_Files/Doxygen
cd ~/Downloads/Install_Files/Doxygen

# download it
wget https://github.com/doxygen/doxygen/releases/download/Release_1_10_0/doxygen-1.10.0.linux.bin.tar.gz

# extract it
tar -xf doxygen-1.10.0.linux.bin.tar.gz

# cd into the extracted directory
# - Note: this directory already has a `bin` dir with prebuilt binary
#   executables. 
cd doxygen-1.10.0

# make and install it
sudo make
sudo make install

# Ensure it's installed
# Example output:
#
#       1.10.0 (ebc57c6dd303a980bd19dd74b8b61c8f3f5180ca)
#
doxygen --version

# Check your man pages available by typing `man doxy` and pressing Tab twice. 
# Output:
#
#       doxygen      doxyindexer  doxysearch   doxywizard  
# 

# View those man pages
man doxygen
man doxyindexer
man doxysearch
man doxywizard
```

The other tools that came with your doxygen download above are available in the `doxygen-1.10.0/bin/` directory which you extracted from the `.tar.gz` file above. Get access to those executables by adding that dir to your `PATH` environment variable. To do that, add the following lines to the bottom of your `~/.bashrc` file:

```bash
# Add doxygen to the PATH
DIR="$HOME/Downloads/Install_Files/Doxygen/doxygen-1.10.0/bin"
if [ -d "$DIR" ]; then
    PATH="$DIR:$PATH"
fi
```

Now re-source your `~/.bashrc` file to apply the changes, and test the new executables:

```bash
# re-source your ~/.bashrc file
. ~/.bashrc

# Install the libxapian.so.30 shared object library, required by 
# `doxysearch.cgi`
# Note: If you are missing this library and you run `doxysearch.cgi`, you'll
# see this error:
# 
#       doxysearch.cgi: error while loading shared libraries: libxapian.so.30: 
#       cannot open shared object file: No such file or directory
#
sudo apt update
sudo apt install libxapian30

# Test the new doxygen executables from the `doxygen-1.10.0/bin/` dir
doxygen --version  # should be the same as above
doxyindexer --version
doxysearch.cgi --version
doxywizard --version  # opens a GUI popup window with version info.
```

To run the GUI-based doxygen configuration file editor, run `doxywizard` at the command line.


## Install GraphViz

`doxygen` requires GraphViz to generate call graphs and class diagrams via the `dot` utility. So install GraphViz, and the `dot` utility, like this:
```bash
sudo apt update
sudo apt install graphviz

# Ensure it is now installed
dot -V  # shows the version
```


## Use the `doxygen` executable

Basic Doxygen usage:

```bash
# Create a new Doxygen configuration file named Doxyfile
doxygen -g Doxyfile
```

Now edit the `Doxyfile` to your liking, either manually or in the GUI `doxywizard` tool by running `doxywizard`. 

You can also use the `doxywizard` GUI to create and edit the `Doxyfile` configuration file. Just run `path/to/doxygen-1.10.0/bin/doxywizard` at the command line. See below for more info.

Then, run `doxygen` to generate the documentation (note that `time` just times how long it takes, and is optional):
```bash
time doxygen Doxyfile
```


## Doxyfile configuration

For a lot more info. and recommended settings, see my notes in my [eRCaGuy_dotfiles](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles) repo here: [Doxygen installation and setup](https://github.com/ElectricRCAircraftGuy/eRCaGuy_dotfiles/tree/master/Doxygen). 

I also have these files there: 

> 1. `Doxyfile_CUSTOMIZED` - my doxygen configuration file with my recommended settings after going through the "Setup and usage" section below.
> 1. `Doxyfile_DEFAULT` - the default doxyfile created by running `doxygen -g Doxyfile`.
> 1. `Doxyfile_run_doxygen.sh` - A script to:
>     1. automatically generate Doxygen documentation for a C or C++ project
>     1. store repo info. into a special readme at path `"$OUTPUT_DIRECTORY/doxygen_info_README.md"`, next to the doxygen output, and 
>     1. open the `index.html` Doxygen output webpage in the Google Chrome web browser.


<!--

## Other things contained inside the `doxygen-1.10.0/` dir you extracted

Installing `doxygen` at the command-line above 

- Binary files are contained in `doxygen-1.10.0/bin/`.

    They include the following:

    1. `doxygen` - the main doxygen executable which you have now installed for use at the command-line. 
    1. `doxyindexer` - a tool to generate a search index for the doxygen search engine.
    doxygen
    doxyindexer
    doxysearch.cgi
    doxywizard
    ```
-->
