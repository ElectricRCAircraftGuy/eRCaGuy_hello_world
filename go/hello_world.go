///usr/bin/env go run "$0" "$@"; exit

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Started Mar. 2022

(description)
STATUS: wip (work in progress)

To compile and run (assuming you've already `cd`ed into this dir):
```bash
# As a bash-like executable
./hello_world.go

# Build and run independently
go build -o bin/ hello_world.go && bin/hello_world

# Build and run all at once
go run hello_world.go
```

References:
1. My build notes:
    1. eRCaGuy_hello_world/go/README.md
    1. https://stackoverflow.com/a/75491520/4561887
1. What's the appropriate Go shebang line? -
   https://stackoverflow.com/q/7707178/4561887
1. Shebang starting with `//`? - https://unix.stackexchange.com/a/162535/114401
1.

*/


package main

import "fmt"
import "os"


func main() {
    fmt.Println("Go: Hello World.")

    os.Exit(1)
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/go$ ./hello_world.go
    Go: Hello World.
    exit status 1

    eRCaGuy_hello_world/go$ go build -o bin/ hello_world.go && bin/hello_world
    Go: Hello World.

    eRCaGuy_hello_world/go$ go run hello_world.go
    Go: Hello World.
    exit status 1
*/
