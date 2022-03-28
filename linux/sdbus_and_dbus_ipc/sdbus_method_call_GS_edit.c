/*
This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

Learn to call an sdbus method (separate/remote-process function) from a C program.

This C program simply does in C what is the equivalent of this call from the command-line:
```bash
busctl call org.freedesktop.systemd1 /org/freedesktop/systemd1 org.freedesktop.systemd1.Manager StartUnit ss "cups.service" "replace"
```
What that command-line command above does is call a method to a separate, running process on the
same PC, via an sdbus method call.
See: http://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html

STATUS: done! works!

To compile and run (assuming you've already `cd`ed into this dir):
NOTE: RUNNING THIS PROGRAM WILL REQUEST a sudo pw from you to run it! That is expected.
From the 1st reference below:
> Make sure to run it as root though, since access to the StartUnit method is privileged:
1. In C:
```bash
gcc -Wall -Wextra -Werror -O3 -std=c17 sdbus_method_call.c -o bin/a -lm $(pkg-config --cflags --libs libsystemd) && bin/a
```
2. In C++
```bash
g++ -Wall -Wextra -Werror -O3 -std=c++17 sdbus_method_call.c -o bin/a $(pkg-config --cflags --libs libsystemd) && bin/a
```

References:
1. *****http://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html - see
  "Invoking a Method, from C, with sd-bus"

*/

#include <stdio.h>
#include <stdlib.h>
#include <systemd/sd-bus.h>

int main(int argc, char *argv[]) {
        // GS: prevent "unused parameter" error
        (void)argc;
        (void)argv;

        sd_bus_error error = SD_BUS_ERROR_NULL;
        sd_bus_message *m = NULL;
        sd_bus *bus = NULL;
        const char *path;
        int r;

        /* Connect to the system bus */
        r = sd_bus_open_system(&bus);
        if (r < 0) {
                fprintf(stderr, "Failed to connect to system bus: %s\n", strerror(-r));
                goto finish;
        }

        /* Issue the method call and store the respons message in m */
        r = sd_bus_call_method(bus,
                               "org.freedesktop.systemd1",           /* service to contact */
                               "/org/freedesktop/systemd1",          /* object path */
                               "org.freedesktop.systemd1.Manager",   /* interface name */
                               "StartUnit",                          /* method name */
                               &error,                               /* object to return error in */
                               &m,                                   /* return message on success */
                               "ss",                                 /* input signature */
                               "cups.service",                       /* first argument */
                               "replace");                           /* second argument */
        if (r < 0) {
                fprintf(stderr, "Failed to issue method call: %s\n", error.message);
                goto finish;
        }

        /* Parse the response message */
        r = sd_bus_message_read(m, "o", &path);
        if (r < 0) {
                fprintf(stderr, "Failed to parse response message: %s\n", strerror(-r));
                goto finish;
        }

        printf("Queued service job as %s.\n", path);

finish:
        sd_bus_error_free(&error);
        sd_bus_message_unref(m);
        sd_bus_unref(bus);

        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}

/*
SAMPLE OUTPUT:

In C:

If you do NOT type in your sudo password to run it, when prompted:

    eRCaGuy_hello_world/linux/sdbus_and_dbus_ipc/TODO$ gcc -Wall -Wextra -Werror -O3 -std=c17 sdbus_method_call.c -o bin/a -lm $(pkg-config --cflags --libs libsystemd) && bin/a
    Failed to issue method call: Permission denied

If you DO type in your sudo password when prompted:

    eRCaGuy_hello_world/linux/sdbus_and_dbus_ipc/TODO$ gcc -Wall -Wextra -Werror -O3 -std=c17 sdbus_method_call.c -o bin/a -lm $(pkg-config --cflags --libs libsystemd) && bin/a
    Queued service job as /org/freedesktop/systemd1/job/3404.


OR, in C++:

If I DO type in the sudo password when prompted:

    eRCaGuy_hello_world/linux/sdbus_and_dbus_ipc/TODO$ g++ -Wall -Wextra -Werror -O3 -std=c++17 sdbus_method_call.c -o bin/a $(pkg-config --cflags --libs libsystemd) && bin/a
    Queued service job as /org/freedesktop/systemd1/job/3576.


*/
