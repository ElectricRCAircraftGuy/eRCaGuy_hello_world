///usr/bin/env rustc "$0" -o /tmp/a && /tmp/a "$@"; exit
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
rustc hello.rs --out-dir bin && bin/hello
```

References:
1. This code was originally learned from the official "Rust By Example" online book here:
   https://doc.rust-lang.org/stable/rust-by-example/hello.html
1.

*/


// line comment

/*
block
comment
*/

// This is the main function.
fn main()
{
    // Statements here are executed when the compiled binary is called.

    // Print text to the console via the `println!()` macro.
    println!("Hello World!");
    println!("I'm a Rustacean!");
}


/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/rust$ rustc hello.rs --out-dir bin && bin/hello
    Hello World!
    I'm a Rustacean!

    eRCaGuy_hello_world/rust$ ./hello.rs
    Hello World!
    I'm a Rustacean!

*/
