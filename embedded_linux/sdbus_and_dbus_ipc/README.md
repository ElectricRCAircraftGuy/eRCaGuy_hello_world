This file is part of eRCaGuy_hello_world: https://github.com/ElectricRCAircraftGuy/eRCaGuy_hello_world

# sdbus Resources and References

1. [The new sd-bus API of systemd](http://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html) - 19 Jun. 2015 - an _excellent_ intro. to sdbus, with example code demos, by Lennart Poettering, original author of systemd and sdbus.
1. [systemd-by-example repo and book](https://gitlab.com/franks_reich/systemd-by-example), by Frank Krick
    1. See especially section ["5.2. Systemd DBus library sd-bus"](https://gitlab.com/franks_reich/systemd-by-example#52-systemd-dbus-library-sd-bus)
1. Official D-Bus Specification: https://dbus.freedesktop.org/doc/dbus-specification.html
    1. See especially the ["Summary of types" table](https://dbus.freedesktop.org/doc/dbus-specification.html#id-1.3.8) for what characters you can put inside message "signatures". 
    1. See also my PDF with notes and highlighting: [D-Bus_Specification_GS_edit.pdf](D-Bus_Specification_GS_edit.pdf)
1. Official, full systemd API--full index or list of ALL functions and things in systemd and sdbus - https://www.freedesktop.org/software/systemd/man/index.html


# Commands to interact with sdbus from the Linux command-line:

See: http://0pointer.net/blog/the-new-sd-bus-api-of-systemd.html

```bash
busctl
busctl tree org.freedesktop.login1
busctl introspect org.freedesktop.login1 /org/freedesktop/login1/session/_31
# Lock your screen
busctl call org.freedesktop.login1 /org/freedesktop/login1/session/_31 org.freedesktop.login1.Session Lock
busctl call org.freedesktop.systemd1 /org/freedesktop/systemd1 org.freedesktop.systemd1.Manager StartUnit ss "cups.service" "replace"
```
