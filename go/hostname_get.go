///usr/bin/env go run "$0" "$@"; exit

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
Learn to get the hostname in Go.
14 Feb. 2023

STATUS: done and works!

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# As a bash-like executable
./hostname_get.go

# Build and run independently
go build -o bin/ hostname_get.go && bin/hostname_get

# Build and run all at once
go run hostname_get.go
```

References:
1. See below.

*/


package main

import "fmt"
import "os"


func main() {
    fmt.Println("Go: Hello World.")

    // Get the hostname. Note that at the terminal this would simply be
    // `hostname`, and in C or C++ you'd use `gethostname()`:
    // https://man7.org/linux/man-pages/man2/gethostname.2.html
    // See: https://pkg.go.dev/os#Hostname
    hostname, err := os.Hostname()
    if err != nil {
        fmt.Println("Error: failed to get hostname; err = ", err)
    }

    fmt.Println("hostname = ", hostname)

    os.Exit(1)
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/go$ ./hostname_get.go
    Go: Hello World.
    hostname =  my_hostname
    exit status 1

*/
