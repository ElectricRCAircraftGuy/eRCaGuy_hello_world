This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Go (Golang)


## References

1. **Getting started with Go**
    1. https://learnxinyminutes.com/docs/go/
    1. Tutorial: Get started with Go: https://go.dev/doc/tutorial/getting-started
    1. https://go.dev/ - official Go website
    1. https://www.tutorialspoint.com/go/index.htm
1. [my answer] [How to specify an output name or path when building in Go (golang)](https://stackoverflow.com/a/75491520/4561887)
1. [my answer] [What's the appropriate Go shebang line?](https://stackoverflow.com/a/75491727/4561887)


## Common commands, building, and help

**Notes:**  
1. Go is a _compiled_ language! It is NOT an interpreted or "scripted" or "script-based" language! `go run` actually _compiles_ and runs in one command. 
    1. See: [Is Google's Golang an interpreter or compiler?](https://stackoverflow.com/q/12249364/4561887)

See especially:
1. [my answer] [How to specify an output name or path when building in Go (golang)](https://stackoverflow.com/a/75491520/4561887)

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

# very short help output
go build --help

# Build `hello_world.go` into an executable named "hello_world" inside your **current
# directory** (NOT necessarily inside the directory where your .go file being built is
# located).
go build hello_world.go 
```

From my answer above:

```bash
# ---------------------
# general formats
# ---------------------

# 1. build input file "filename.go" into an executable
# named "executable_filename" within the directory you are currently `cd`ed
# into
go build -o executable_filename filename.go

# 2. build input file "filename.go" into an executable at
# path "output_dir/filename"; this automatically creates directory "output_dir"
# if it does not already exist
go build -o output_dir/ filename.go

# 3. build input file "filename.go" into an executable at
# path "output_dir/whatever"; this automatically creates directory "output_dir"
# if it does not already exist
go build -o output_dir/whatever filename.go

# ---------------------
# examples
# ---------------------

# create executable "whatever" from "hello_world.go"
go build -o whatever hello_world.go

# make directory "bin" and create executable "bin/hello_world"
# from "hello_world.go"
go build -o bin/ hello_world.go

# make directory "bin" and create executable "bin/whatever"
# from "hello_world.go"
go build -o bin/whatever hello_world.go
```

```bash
# see the short help menu for `go run`
go run --help

# see the long help menu for `go run`
go help run

# build and run this file all at once!
go run hello_world.go
```


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


## TODO

1. [ ] finish the hello_world.go demo
1. [ ] Figure out and add a shebang line which will compile and run go
    1. [Google search for "hashbang for go"](https://www.google.com/search?q=hashbang+for+go&oq=hashbang+for+go&aqs=chrome..69i57.2310j0j7&sourceid=chrome&ie=UTF-8)
    1. [What's the appropriate Go shebang line?](https://stackoverflow.com/q/7707178/4561887)
    1. \*\*\*\*\*+ https://unix.stackexchange.com/a/162535/114401
    1. [Run C or C++ file as a script](https://stackoverflow.com/a/29709521/4561887)
