///usr/bin/env rustc gcc -Wall -Wextra -Werror -O3 -std=gnu17 "$0" -o /tmp/a -lm && /tmp/a "$@"; exit
// For the line just above, see my answer here: https://stackoverflow.com/a/75491834/4561887

/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

(description)
STATUS: (status)

keywords to easily grep or ripgrep in this repo for this program and what it teaches
KEYWORDS:

To compile and run (assuming you've already `cd`ed into this dir):
```bash
./hello.rs

# OR
rustc hello.rs && ./hello
```

References:
1. This code was originally copied and modified from here:
   https://doc.rust-lang.org/stable/rust-by-example/hello.html
1.

*/


// line comment

/*
block
comment
*/

// This is the main function.
fn main() {
    // Statements here are executed when the compiled binary is called.

    // Print text to the console via the `println!()` macro.
    println!("Hello World!");
    println!("I'm a Rustacean!");
}


/*
SAMPLE OUTPUT:



*/
