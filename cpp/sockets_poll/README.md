This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Let's get a poll demo setup to see if it can build and run on both Linux and Windows via MSYS2. 


# Instructions

1. Follow the setup instructions here: "Linux Setup" or "Windows Setup": https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2

1. Build:
    ```bash
    make clean
    make
    ```

1. Run:
    
    Server terminal: in one terminal:
    ```bash
    ./build/Portable/poll_server
    ```

    Client terminal: in another terminal:
    ```bash
    # Send a message to the server via localhost
    printf "%s" "hello" | nc 127.0.0.1 12345
    # Then press Ctrl + C to kill the connection
    ```

1. Output
    In the server terminal, you will see: 
    ```bash
    eRCaGuy_hello_world/cpp/sockets_poll$ ./build/Portable/poll_server 
    Waiting on poll()...
      Listening socket is readable
      New incoming connection - 4
    Waiting on poll()...
      Descriptor 4 is readable
      5 bytes received
      Connection closed
    Waiting on poll()...
    ```

    "Connection closed" does not happen until you press <kbd>Ctrl</kbd> + <kbd>C</kbd> in the client terminal, above. 


# Windows result: 



