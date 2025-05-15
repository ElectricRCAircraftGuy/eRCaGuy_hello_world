This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world


# MPMC (Multi-Producer Multi-Consumer) Thread-safe Queue


# Instructions

1. Follow the setup instructions here: "Linux Setup" or "Windows Setup": https://github.com/ElectricRCAircraftGuy/eRCaGuy_Linux_Windows_CMake_Sockets_MSYS2

1. Build:
    ```bash
    make clean
    make
    ```

1. Run:
    
    ```bash
    ./build/Portable/mpmc_queue
    ```

1. Output
    Example run and output:

    ```bash
    eRCaGuy_hello_world/cpp/mpmc_thread_safe_queue$ ./build/Portable/mpmc_queue
    Adding value 83
    Adding value 86
    Adding value 77
    Adding value 15
    Adding value 62
    Adding value 90
    Adding value 63
    Adding value 40
    Adding value 86
    Adding value 93
    Adding value 11
    Adding value 67
    Adding value 82
    Adding value 62
    Adding value 67
    Adding value 29
    Adding value 22
    Adding value 69
    Adding value 93
    Adding value 56
      Removing value 83
      Removing value 86
      Removing value 77
      Removing value 15
      Removing value 62
      Removing value 90
      Removing value 63
      Removing value 40
      Removing value 86
      Removing value 93
      Removing value 11
      Removing value 67
      Removing value 82
      Removing value 62
      Removing value 67
      Removing value 29
      Removing value 69
      Removing value 93
      Removing value 56
      Removing value 22
    Adding value 29
      Removing value 29
    Adding value 21
      Removing value 21
    Adding value 84
      Removing value 84
    Adding value 98
      Removing value 98
    Adding value 15
      Removing value 15
    Adding value 13
      Removing value 13
    Adding value 91
      Removing value 91
    Adding value 56
      Removing value 56
    Adding value 62
      Removing value 62
    Adding value 96
      Removing value 96
    Adding value 5
      Removing value 5
    Adding value 84
      Removing value 84
    Adding value 36
      Removing value 36
    Adding value 46
      Removing value 46
    Adding value 13
      Removing value 13
    Adding value 24
      Removing value 24
    Adding value 82
      Removing value 82
    Adding value 14
      Removing value 14
    Adding value 34
      Removing value 34
    Adding value 43
      Removing value 43
    Adding value 87
      Removing value 87
    Adding value 76
      Removing value 76
    Adding value 88
      Removing value 88
    Adding value 3
      Removing value 3
    Adding value 54
      Removing value 54
    Adding value 32
    Adding value 60
      Removing value 32
      Removing value 60
    Adding value 39
      Removing value 39
    Adding value 26
      Removing value 26
    Adding value 94
      Removing value 94
    Adding value 95
      Removing value 95
    Adding value 34
      Removing value 34
    Adding value 67
      Removing value 67
    Adding value 97
      Removing value 97
    Adding value 17
      Removing value 17
    Adding value 52
      Removing value 52
    Adding value 1
      Removing value 1
    Adding value 86
      Removing value 86
    Adding value 65
      Removing value 65
    Adding value 44
      Removing value 44
    Adding value 40
      Removing value 40
    Adding value 31
      Removing value 31
    Adding value 97
      Removing value 97
    Adding value 81
      Removing value 81
    Adding value 9
      Removing value 9
    Adding value 67
      Removing value 67
    Adding value 97
      Removing value 97
    Adding value 86
      Removing value 86
    Adding value 6
      Removing value 6
    Adding value 19
      Removing value 19
    Adding value 28
      Removing value 28
    Adding value 32
      Removing value 32
    Adding value 3
      Removing value 3
    Adding value 70
      Removing value 70
    Adding value 8
      Removing value 8
    Adding value 40
      Removing value 40
    Adding value 96
      Removing value 96
    Adding value 18
      Removing value 18
    Adding value 46
      Removing value 46
    Adding value 21
      Removing value 21
    Adding value 79
      Removing value 79
    Adding value 64
      Removing value 64
    Adding value 41
      Removing value 41
    Adding value 93
    Adding value 34
      Removing value 93
      Removing value 34
    Adding value 24
      Removing value 24
    Adding value 87
      Removing value 87
    Adding value 43
      Removing value 43
    Adding value 27
      Removing value 27
    Adding value 59
      Removing value 59
    Adding value 32
      Removing value 32
    Adding value 37
      Removing value 37
    Adding value 75
      Removing value 75
    Adding value 74
      Removing value 74
    Adding value 58
    Adding value 29
      Removing value 58
      Removing value 29
    Adding value 35
    Adding value 93
      Removing value 35
      Removing value 93
    Adding value 43
      Removing value 43
    Adding value 28
      Removing value 28
    Adding value 76
      Removing value 76
    Adding value 43
      Removing value 43
    Adding value 13
      Removing value 13
    Adding value 6
      Removing value 6
    Adding value 4
      Removing value 4
    Adding value 28
      Removing value 28
    Adding value 69
      Removing value 69
    Adding value 17
      Removing value 17
    Adding value 24
      Removing value 24
    Adding value 70
      Removing value 70
    Adding value 90
      Removing value 90
    Adding value 72
      Removing value 72
    Adding value 44
    Adding value 5
    Adding value 54
    Adding value 69
    Adding value 42
    Adding value 97
    Adding value 55
    Adding value 48
    Adding value 22
    Adding value 99
    Adding value 46
    Adding value 40
    Adding value 11
    Adding value 5
    Adding value 61
    Adding value 78
    Adding value 20
    Adding value 44
    Adding value 22
    Adding value 8
    Adding value 82
    Adding value 24
    Adding value 62
    Adding value 0
    Adding value 52
    ```

