This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# Bash library: `ansi_text_format_lib.sh`


# See also

1. [GabrielStaples.com: How do you write, import, use, and test libraries in Bash?](https://gabrielstaples.com/bash-libraries/#gsc.tab=0)


# Example usage

1. Download the library
    ```bash
    curl -LO https://raw.githubusercontent.com/ElectricRCAircraftGuy/eRCaGuy_hello_world/master/bash/ansi_text_format_lib.sh
    ```

1. In your bash script, use it like this
    ```bash
    #!/usr/bin/env bash
    
    # import the library
    . ansi_text_format_lib.sh

    # use it

    # Set the format for the `f` variable
    set_f ANSI_BOLD ANSI_UNDERLINE ANSI_SLOW_BLINK ANSI_FG_BR_BLU
    # Now use the `f` and `F` format variables to format text
    echo -e "${f}This string is bold, underlined, blinking, bright blue.${F} This is not."
    ```
