This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# Go (Golang)

Notes:
1. Go is a _compiled_ language! It is NOT an interpreted or "scripted" or "script-based" language! `go run` actually _compiles_ and runs in one command. 
    1. See: [Is Google's Golang an interpreter or compiler?](https://stackoverflow.com/q/12249364/4561887)


## To install Go on Ubuntu:

See: https://go.dev/doc/install

```bash
# prepare a download directory
cd ~/Downloads
mkdir Install_files/Go
cd Install_files/Go

# Download the installation file
# Note: update the URL and file version below with the latest one from here:
# https://go.dev/doc/install
wget https://go.dev/dl/go1.17.8.linux-amd64.tar.gz

# MANUALLY BACK UP THE OLD INSTALLATION DATA AT THIS POINT, IF DESIRED!

# remove old installation, if there was one
sudo rm -rf /usr/local/go
# extract new installation to "/usr/local/go"
sudo tar -C /usr/local -xzf go1.17.8.linux-amd64.tar.gz

# add "/usr/local/go/bin" to your PATH to allow you to run the `go` executable
echo '# add golang executable path to PATH variable' >> ~/.bashrc
echo 'export PATH=$PATH:/usr/local/go/bin' >> ~/.bashrc
# re-source your ~/.bashrc file to bring in that PATH variable change to your current terminal
. ~/.bashrc

# Verify that you have `go` installed by checking its version and ensuring it matches the version
# of the file you downloaded above. Sample output:
#       go version go1.17.8 linux/amd64
go version
```


## Help

```bash
# print main help menu
go help
go --help  # same as above

# get help on a specific command
go help <command>  

# Ex: get help on the `go run` command, which both compiles and runs a go program in one cmd
go help run
# Or get help on the build command
go help build
```


## Getting started with Go

1. https://learnxinyminutes.com/docs/go/
1. Tutorial: Get started with Go: https://go.dev/doc/tutorial/getting-started
1. https://go.dev/ - official Go website


## TODO

1. finish the hello_world.go demo
1. Figure out and add a shebang line which will compile and run go
    1. [Google search for "hashbang for go"](https://www.google.com/search?q=hashbang+for+go&oq=hashbang+for+go&aqs=chrome..69i57.2310j0j7&sourceid=chrome&ie=UTF-8)
    1. [What's the appropriate Go shebang line?](https://stackoverflow.com/q/7707178/4561887)
