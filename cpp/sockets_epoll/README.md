This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Let's get an epoll demo setup to see if it can build and run on both Linux and Windows via MSYS2. 


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
    ./build/Portable/epoll_server
    ```

    Client terminal: in another terminal:
    ```bash
    # Send a message to the server via localhost
    printf "%s" "hello" | nc 127.0.0.1 8080
    # Then press Ctrl + C to kill the connection
    ```

1. Output
    In the server terminal, you will see: 
    ```bash
    eRCaGuy_hello_world/cpp/sockets_epoll$ ./build/Portable/epoll_server 
    Server listening on port 8080
    New connection: 5
    Client disconnected: 5
    ```

    "Client disconnected" does not happen until you press <kbd>Ctrl</kbd> + <kbd>C</kbd> in the client terminal, above. 
