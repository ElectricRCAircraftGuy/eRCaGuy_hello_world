/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

GS
~ Jan. 2022

Q: See if having a file open via the Linux `open()` call means that I can't also read from it using
the C++ `std::ifstream` input file stream at the same time.
A: Yes, you **can** read from the file at the same time in both ways. It works just fine.

To compile and run (assuming you've already `cd`ed into this dir):
1. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 file_open_and_read_by_linux_open_and_std_ifstream_at_once.cpp -o bin/a && bin/a
```

References:
1. Linux `open()`: https://linux.die.net/man/3/open
1. Linux `read()`: https://linux.die.net/man/2/read
1. Linux and C `getline()`: https://man7.org/linux/man-pages/man3/getline.3.html
1. https://en.cppreference.com/w/cpp/io/basic_ifstream - great example to read a file here using
   an **input file stream** class object.
1. *****Full inheritance diagram of the C++ input/output "stream-based IO" library:
   https://en.cppreference.com/w/cpp/io
1. *****MUCH EASIER TO UNDERSTAND than cppreference.com IN THIS CASE!:
   http://www.cplusplus.com/reference/istream/istream/getline/

*/

// Linux includes
#include <fcntl.h>  // `open()`
#include <unistd.h> // `read()`

// C++ includes
#include <fstream>   // `std::ifstream`
#include <iostream>  // For `std::cin`, `std::cout`, `std::endl`, etc.
#include <cstring>    // `strerror()`

// C includes
#include <cstdint>  // For `uint8_t`, `int8_t`, etc.

#include <cstdio>   // For `printf()`

void printFileContents(const std::string& fileContents)
{
    std::cout << "fileContents (" << fileContents.size() << " chars):\n"
                 "------------------------\n";
    std::cout << fileContents << "\n\n";
}

void printFileContentsCStr(const char* fileContents)
{
    printf("fileContents (%zu chars):\n"
           "------------------------\n",
           strlen(fileContents));
    printf("%s\n\n", fileContents);
}

// int main(int argc, char *argv[])  // alternative prototype
int main()
{
    printf("Hello ");
    std::cout << "world!\n\n";

    // Add a few chars to this filename to force the errors to occur and print out below!
    const char* FILENAME = __FILE__; // path to this file
    constexpr size_t NUM_CHARS_TO_PRINT = 1000;
    printf("FILENAME = \"%s\".\n", FILENAME);
    int retcode;


    // 1st, open and read a file using Linux commands `open()` and `read()`
    printf("\n");
    printf("-----------------------------------------------------\n"
           "TECHNIQUE 1: using Linux `open()` and `read()` calls:\n"
           "-----------------------------------------------------\n\n");

    // LINUX `open()`
    // fd means "file descriptor"
    int fd = open(FILENAME, O_RDONLY);
    if (fd < 0)
    {
        printf("ERROR: failed to open file \"%s\". errno = %i; error string = %s\n",
            FILENAME, errno, strerror(errno));
    }
    char buf[NUM_CHARS_TO_PRINT + 1]; // + 1 so we can manually add a null-terminator
    ssize_t bytesRead = read(fd, buf, NUM_CHARS_TO_PRINT);
    if (bytesRead < 0)
    {
        printf("ERROR: failed to read file \"%s\"; bytesRead = %zi; errno = %i; "
               "error string = %s\n",
            FILENAME, bytesRead, errno, strerror(errno));
    }
    else
    {
        // Unlike in Technique 2 below, you must **manually** null terminate the C-string after
        // using Linux's `read()` call!
        buf[bytesRead] = '\0';
        printf("bytesRead = %zi\n"
               "PRINTING OUTPUT:\n"
               "============ FILE START ===========\n"
               "%s\n"
               "============ FILE END =============\n",
            bytesRead, buf);
    }


    // 2nd, open and read the file using C++'s `std::ifstream` class.
    printf("\n");
    printf("-----------------------------------------------------\n"
           "TECHNIQUE 2: using C++ `std::ifstream` class to read:\n"
           "-----------------------------------------------------\n\n");

    // C++ `std::ifstream` input filestream!
    // Constructor documentation for `std::ifstream()`:
    // https://en.cppreference.com/w/cpp/io/basic_ifstream/basic_ifstream
    std::ifstream inputFileStream(FILENAME);
    // print "true" or "false" instead of 1 or 0; see:
    // https://en.cppreference.com/w/cpp/io/manip/boolalpha
    std::cout << std::boolalpha;
    std::cout << "inputFileStream.is_open() = " << inputFileStream.is_open() << "\n";
    std::string fileContents;
    // Option A (easier, and therefore better): use `std::getline()` global func to read an entire
    // line from the open file stream into a **C++ `std::string`**. This reads line 1 (1st line).
    // - `std::getline()` reference: https://en.cppreference.com/w/cpp/string/basic_string/getline
    std::getline(inputFileStream, fileContents);  // <========= EASIEST ========
    printFileContents(fileContents);
    // Option B: use `std::ifstream::getline()` class method to read an entire line from the open
    // file stream into a **C-style** char buffer! This reads line 2 (2nd line).
    // - reference: https://en.cppreference.com/w/cpp/io/basic_ifstream
    //              https://en.cppreference.com/w/cpp/io/basic_istream/getline
    //   FAR EASIER REFERENCE PAGE TO UNDERSTAND:
    //              *****http://www.cplusplus.com/reference/istream/istream/getline/
    char buf2[NUM_CHARS_TO_PRINT];
    inputFileStream.getline(buf2, NUM_CHARS_TO_PRINT);
    printf("(buf2 only):\n");
    printFileContentsCStr(buf2);
    // Note: `buf2` is automatically cast to a `std::string` in this string concatenation via
    // `operator+()` here
    fileContents = fileContents + "\n" + buf2;
    printf("(total fileContents):\n");
    printFileContents(fileContents);

    std::cout <<
    "NOTE: THE ABOVE DEMO OF `std::ifstream()` IS VERY INCOMPLETE. You can also read in chars\n"
    "via its `::get()`, `::read()`, and `::getsome()` class methods. The main point was to simply\n"
    "show that it is really convenient to use when you want to read in a whole line at once, as\n"
    "opposed to the Linux `read()` call which cannot do this as easily. Of the two `getline()`\n"
    "C++ calls, the `std::getLine()` global function is **far easier** to use because it is part\n"
    "of the <string> library and therefore can read directly into a `std::string` instead of\n"
    "into a C-style buffer. See also:\n"
    "   - https://en.cppreference.com/w/cpp/io/basic_istream/get\n"
    "   - https://en.cppreference.com/w/cpp/io/basic_istream/read\n"
    "   - https://en.cppreference.com/w/cpp/io/basic_istream/readsome\n"
    "   - *****https://stackoverflow.com/questions/23664175/whats-the-difference-between-read-readsome-get-and-getline\n";


    // Close the 1st file descriptor (from Linux `open()`)
    retcode = close(fd);
    if (retcode < 0)
    {
        printf("ERROR: failed to close file \"%s\"; errno = %i; error string = %s\n",
            FILENAME, errno, strerror(errno));
    }

    // Explicitly close the associated file of the C++ input file stream
    // https://en.cppreference.com/w/cpp/io/basic_ifstream/close. Note, according to the
    // documentation here (https://en.cppreference.com/w/cpp/io/basic_ifstream), the destructor
    // will destruct the `std::ifstream` object "and the associated buffer", and close the file.
    // Therefore, if you do NOT explicitly call `close()` here, that's still okay! The destructor
    // will automatically close the file for you anyway as the scope of this object is
    // exited below.
    inputFileStream.close();


    return 0;
}



/*
SAMPLE OUTPUT:

    eRCaGuy_hello_world/cpp$ g++ -Wall -Wextra -Werror -O3 -std=c++17 file_open_and_read_by_linux_open_and_std_ifstream_at_once.cpp -o bin/a && bin/a
    Hello world!

    FILENAME = "file_open_and_read_by_linux_open_and_std_ifstream_at_once.cpp".

    -----------------------------------------------------
    TECHNIQUE 1: using Linux `open()` and `read()` calls:
    -----------------------------------------------------

    bytesRead = 1000
    PRINTING OUTPUT:
    ============ FILE START ===========
    /*
    This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

    Q: See if having a file open via the Linux `open()` call means that I can't also read from it using
    the C++ `std::ifstream` input file stream at the same time.
    A: Yes, you **can** read from the file at the same time in both ways. It works just fine.

    To compile and run (assuming you've already `cd`ed into this dir):
    1. In C++
    ```bash
    g++ -Wall -Wextra -Werror -O3 -std=c++17 file_open_and_read_by_linux_open_and_std_ifstream_at_once.cpp -o bin/a && bin/a
    ```

    References:
    1. Linux `open()`: https://linux.die.net/man/3/open
    1. Linux `read()`: https://linux.die.net/man/2/read
    1. Linux and C `getline()`: https://man7.org/linux/man-pages/man3/getline.3.html
    1. https://en.cppreference.com/w/cpp/io/basic_ifstream - great example to read a file here using
       an **input file stream** class object.
    1. *****Full inheritance diagram of the C++ input/output "stream-based IO" library:
       https://
    ============ FILE END =============

    -----------------------------------------------------
    TECHNIQUE 2: using C++ `std::ifstream` class to read:
    -----------------------------------------------------

    inputFileStream.is_open() = true
    fileContents (2 chars):
    ------------------------
    /*

    (buf2 only):
    fileContents (102 chars):
    ------------------------
    This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

    (total fileContents):
    fileContents (105 chars):
    ------------------------
    /*
    This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

    NOTE: THE ABOVE DEMO OF `std::ifstream()` IS VERY INCOMPLETE. You can also read in chars
    via its `::get()`, `::read()`, and `::getsome()` class methods. The main point was to simply
    show that it is really convenient to use when you want to read in a whole line at once, as
    opposed to the Linux `read()` call which cannot do this as easily. Of the two `getline()`
    C++ calls, the `std::getLine()` global function is **far easier** to use because it is part
    of the <string> library and therefore can read directly into a `std::string` instead of
    into a C-style buffer. See also:
       - https://en.cppreference.com/w/cpp/io/basic_istream/get
       - https://en.cppreference.com/w/cpp/io/basic_istream/read
       - https://en.cppreference.com/w/cpp/io/basic_istream/readsome
       - *****https://stackoverflow.com/questions/23664175/whats-the-difference-between-read-readsome-get-and-getline


*/
