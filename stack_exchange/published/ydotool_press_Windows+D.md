<!--
GS
4~17 June 2023

https://askubuntu.com/q/1470593/327339
https://askubuntu.com/questions/1470593/how-can-i-write-a-program-to-press-keys-such-as-windows-d-in-wayland-repla?noredirect=1#comment2577739_1470593

https://github.com/ReimuNotMoe/ydotool
https://askubuntu.com/a/1299008/327339
https://askubuntu.com/questions/903532/how-can-i-add-show-desktop-to-the-gnome-dash-or-ubuntu-dock/1109490#1109490

Update: let's make this a website article first instead! 
I'll put it here: https://gabrielstaples.com/ydotool-tutorial/
Filename: 2023-06-17-ydotool-tutorial.md

I'll put bits of it here too: 
1. My Q: https://askubuntu.com/q/1470593/327339
1. https://askubuntu.com/q/956640/327339
-->


# Tutorial: Getting started with `ydotool` to automate key presses (or mouse movements) in Linux


## `ydotool` works well in both the X11 _and_ Wayland window managers to press any keys, including <kbd>Windows</kbd> + <kbd>D</kbd>, for example

Here is a full tutorial.

Note: `ydotool` is a universal replacement of `xdotool`, which is a tool to move the mouse and do keypresses in the X11 window manager. The `ydotool` program was created because `xdotool` doesn't work in Wayland, which is the new window manager that Ubuntu is slowly moving towards, even though Wayland currently [is still very buggy should be turned _off_ in most cases](https://askubuntu.com/a/1470563/327339).

_Tested on Ubuntu 22.04.2 with both the X11 and Wayland window managers (for how to change between the two, see my notes and screenshots [in my answer here](https://askubuntu.com/a/1470563/327339))._


## 1. Build and install `ydotool`:

See: <https://github.com/ReimuNotMoe/ydotool#build>. 

First, build and install it:
```bash
# install dependencies
sudo apt update
sudo apt install git cmake scdoc

# build ydotool
# See: https://github.com/ReimuNotMoe/ydotool#build
git clone https://github.com/ReimuNotMoe/ydotool.git
cd ydotool
mkdir build
cd build
cmake ..                 # takes < 1 second
time make -j "$(nproc)"  # takes < 1 second
sudo make install
# Note: the install command installs here:
#
#       -- Install configuration: ""
#       -- Installing: /usr/local/bin/ydotoold
#       -- Installing: /usr/local/bin/ydotool
#       -- Installing: /usr/lib/systemd/user/ydotool.service
#       -- Installing: /usr/local/share/man/man1/ydotool.1
#       -- Installing: /usr/local/share/man/man8/ydotoold.8

# See the man pages for help, and to prove to yourself it is installed
man ydotool   # for the main program
man ydotoold  # for the background daemon process
# help menu
ydotool -h    # for the main program
ydotoold -h   # for the background daemon process [VERY HELPFUL MENU!]

# check the version; my output is `v1.0.4-0-g57ba7d0`
ydotoold --version
```


## 2. Now, use it: have `ydotool` press <kbd>Windows</kbd> + <kbd>D</kbd>

#### Quick summary:
```bash
# 1. start the `ydotoold` background daemon (`sudo -b` runs it in the
# background; see `sudo -h`).
# - It takes a couple seconds to fully start up and print "READY". Once it does
#   that, hit Enter a couple times to clear out the command line.
sudo -b ydotoold --socket-path="$HOME/.ydotool_socket" --socket-own="$(id -u):$(id -g)"

# 2. Use `ydotool`
# - Have ydotool press Windows + D once to hide all windows, then make it wait 2
#   seconds, then have it press Windows + D again to show all windows:
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0; \
    sleep 2; \
    YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0

# 3. Additional commands you may need: to show, kill, and help

# See the `ydotoold` background running processes
ps auxf | grep ydotoold

# Kill the `ydotoold` background running processes
sudo pkill ydotoold

# View the `ydotool` main help menu, including a list of all sub-commands.
ydotool -h

# View the `ydotool` sub-command help menus. 
# - Bug ( https://github.com/ReimuNotMoe/ydotool/issues/206 ): the daemon *must*
#   be running first to see these help menus!
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key -h
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool click -h
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool mousemove -h
# etc. 

# Open the Linux C header file containing all available key codes that `ydotool`
# can press
gedit /usr/include/linux/input-event-codes.h
```

#### Details:

```bash
# In one terminal, start the required background daemon process as root, but
# setting its socket file to be accessible by your main user withOUT `sudo`. 
# - Allowing our user to access this daemon withOUT running it as `root` is
#   accomplished by setting the owner of the socket file to our own user via
#   the `--socket-path="$HOME/.ydotool_socket" --socket-own="$(id -u):$(id -g)"` 
#   options.
# - It takes a couple seconds to fully start up and print "READY". Once it does
#   that, hit Enter a couple times to clear out the command line.
sudo -b ydotoold --socket-path="$HOME/.ydotool_socket" --socket-own="$(id -u):$(id -g)"

# In the same terminal, or another terminal, send a signal to this running
# background daemon via the open socket inter-process-communication
# (IPC) pseudo-file. Here, we send the Windows + D shortcut key:
#
# Windows + D press and release: window toggle: this hides all windows.
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0
```

The `125:1 32:1 32:0 125:0` key codes tell the program to, in this order: "press the Windows key, press the D key, release the D key, release the Windows key".

That's it! 

Manually press <kbd>Windows</kbd> + <kbd>D</kbd> now to show all windows again so you can see your terminal. 

I'll talk about what the `key 125:1 32:1 32:0 125:0` part means farther below.

Note that `sudo -b` runs this daemon as a background process. If you leave off `-b`, then you'll have to use two separate terminals, as the daemon will take up the first terminal. 

You can leave the background `ydotoold` background daemon running forever, but if you'd like to kill it, here's how:
1. Kill `ydotoold`:
    ```bash
    sudo pkill ydotoold
    ```
1. (Optional) see if `ydotoold` is running:
    ```bash
    ps auxf | grep ydotoold
    ```

    Example run and output *before* killing `ydotoold`. As you can see, my single call to `ydotoold` above actually spawned *3* `ydotoold` processes, because the one I called spawned a sub process, which spawned a sub sub process.
    ```bash
    $ ps auxf | grep ydotoold
    root     1772293  0.0  0.0  23004  5952 pts/4    S    22:00   0:00  |   |   \_ sudo ydotoold --socket-path=/home/gabriel/.ydotool_socket --socket-own=1000:1000
    root     1772304  0.0  0.0  23004   944 pts/6    Ss+  22:00   0:00  |   |   |   \_ sudo ydotoold --socket-path=/home/gabriel/.ydotool_socket --socket-own=1000:1000
    root     1772305  0.0  0.0   2776   956 pts/6    S    22:00   0:00  |   |   |       \_ ydotoold --socket-path=/home/gabriel/.ydotool_socket --socket-own=1000:1000
    gabriel+ 1792351  0.0  0.0  17864  2476 pts/4    S+   22:09   0:00  |   |   \_ grep --color=auto ydotoold
    ```
1. Here is what the main `ydotool` help menu looks like. It shows the various sub-commands available:
    ```bash
    $ ydotool -h
    Usage: ydotool <cmd> <args>
    Available commands:
      click
      mousemove
      type
      key
      debug
      bakers
    Use environment variable YDOTOOL_SOCKET to specify daemon socket.
    ```
1. Here are some of the sub-command menus. Note that due to [this bug](https://github.com/ReimuNotMoe/ydotool/issues/206), you _must_ have the `ydotoold` daemon running first in order for the sub-command help menus to show up:
    1. `key`: `YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key -h`
        ```bash
        $ YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key -h
        Usage: key [OPTION]... [KEYCODES]...
        Emit key events.

        Options:
          -d, --key-delay=N          Delay N milliseconds between key events
          -h, --help                 Display this help and exit

        Since there's no way to know how many keyboard layouts are there in the world,
        we're using raw keycodes now.

        Syntax: <keycode>:<pressed>
        e.g. 28:1 28:0 means pressing on the Enter button on a standard US keyboard.
             (where :1 for pressed means the key is down and then :0 means the key is released)     
             42:1 38:1 38:0 24:1 24:0 38:1 38:0 42:0 - "LOL"

        Non-interpretable values, such as 0, aaa, l0l, will only cause a delay.

        See `/usr/include/linux/input-event-codes.h' for available key codes (KEY_*).
        ```
    1. `click`: `YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool click -h`
        ```bash
        $ YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool click -h
        Usage: click [OPTION]... [BUTTONS]...
        Click mouse buttons.

        Options:
          -r, --repeat=N             Repeat entire sequence N times
          -D, --next-delay=N         Delay N milliseconds between input events (up/down,                                
                                     a complete click means doubled time)
          -h, --help                 Display this help and exit

        How to specify buttons:
          Now all mouse buttons are represented using hexadecimal numeric values, with an optional
        bit mask to specify if mouse up/down needs to be omitted.
          0x00 - LEFT
          0x01 - RIGHT
          0x02 - MIDDLE
          0x03 - SIDE
          0x04 - EXTR
          0x05 - FORWARD
          0x06 - BACK
          0x07 - TASK
          0x40 - Mouse down
          0x80 - Mouse up
          Examples:
            0x00: chooses left button, but does nothing (you can use this to implement extra sleeps)
            0xC0: left button click (down then up)
            0x41: right button down
            0x82: middle button up
          The '0x' prefix can be omitted if you want.
        ```
    1. `mousemove`: `YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool mousemove -h`
        ```bash
        $ YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool mousemove -h
        Usage: mousemove [OPTION]... [-x <xpos> -y <ypos>] [-- <xpos> <ypos>]
        Move mouse pointer or wheel.

        Options:
          -w, --wheel                Move mouse wheel relatively
          -a, --absolute             Use absolute position, not applicable to wheel
          -x, --xpos                 X position
          -y, --ypos                 Y position
          -h, --help                 Display this help and exit

        You need to disable mouse speed acceleration for correct absolute movement.
        ```

Voila! I'm so happy I got this working! I now have a viable means of getting my ["show desktop"](https://askubuntu.com/a/1109490/327339) button to work again once I am forced to use Wayland, and once it [is less buggy](https://askubuntu.com/a/1470563/327339) and actually functions right.


## What do keycodes `125:1 32:1 32:0 125:0` mean, and how do I find key codes I want to use?

See the `YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key -h` help menu above. It states: 

```bash
Syntax: <keycode>:<pressed>
e.g. 28:1 28:0 means pressing on the Enter button on a standard US keyboard.
     (where :1 for pressed means the key is down and then :0 means the key is released)     
     42:1 38:1 38:0 24:1 24:0 38:1 38:0 42:0 - "LOL"

Non-interpretable values, such as 0, aaa, l0l, will only cause a delay.

See `/usr/include/linux/input-event-codes.h' for available key codes (KEY_*).
```

So, open up your Linux `/usr/include/linux/input-event-codes.h` file to see all key codes:
```bash
# (my preference) open in the Sublime Text GUI
subl /usr/include/linux/input-event-codes.h
# open in the gedit GUI
gedit /usr/include/linux/input-event-codes.h
# open in nano (Ctrl + x to exit)
nano /usr/include/linux/input-event-codes.h
# open in vim (:q then Enter to exit)
vi /usr/include/linux/input-event-codes.h
```

You can see what appears to be a _more-recent version_ of this file online in the Linux kernel here: <https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h>. 

As you can see [in that file here](https://github.com/torvalds/linux/blob/master/include/uapi/linux/input-event-codes.h#L202), key code `125` is the `KEY_LEFTMETA`: 

>     #define KEY_LEFTMETA      125

Key code `32` is `KEY_D`: 

>     #define KEY_D         32

A [Google search for "input-event-codes.h which is the super or windows key?"](https://www.google.com/search?q=input-event-codes.h+which+is+the+super+or+windows+key%3F&oq=input-event-codes.h+which+is+the+super+or+windows+key%3F&aqs=chrome..69i57.477j0j9&sourceid=chrome&ie=UTF-8) helped me find [this](https://github.com/PixlOne/logiops/issues/201#issuecomment-773745032), where @hasimsait said it was `KEY_LEFTMETA`. That's how I knew to use that key for the <kbd>Windows</kbd> (<kbd>Super</kbd>) key. 

From the `ydotool key -h` help menu above, we learned: `Syntax: <keycode>:<pressed>`, where `1` is pressed, and `0` is not pressed. So, `32:1 32:0` means to press and then release the <kbd>D</kbd> key. That would type a lower-case `d` if your cursor was in a text editor. 

Therefore, `125:1 32:1 32:0 125:0` means, in this order: "press the Windows key, press the D key, release the D key, release the Windows key". 

Notice that to activate the <kbd>Windows</kbd> + <kbd>D</kbd> shortcut key, you must _release the buttons in the opposite order they were pressed!_ You hold the <kbd>Windows</kbd> key while pressing and releasing the <kbd>D</kbd> key. So, be sure to release the buttons with `<keycode>:0` in the _opposite order_ that you pressed them.


## Warnings in Wayland

Note that I see this in the output when I run my `ydotoold` command above _in Wayland_ only:

> WARNING: running xinput against an Xwayland server. See the xinput man page for details.  
> unable to find device pointer:ydotoold virtual device

I don't really know what it means, but it seems important. Here is the full run and output:
```bash
$ sudo ydotoold --socket-path="$HOME/.ydotool_socket" --socket-own="$(id -u):$(id -g)"
[sudo] password for gabriel: 
Socket path: /home/gabriel/.ydotool_socket
Removing old stale socket
Socket permission: 0600
Socket ownership: UID=1000, GID=1000
READY
WARNING: running xinput against an Xwayland server. See the xinput man page for details.
unable to find device pointer:ydotoold virtual device
```

`man xinput` shows the following, but again, I don't really understand what this means either:

> XWAYLAND
>
>        Xwayland is an X server that uses  a  Wayland  Compositor  as  backend.
>        Xwayland  acts as translation layer between the X protocol and the Way‐
>        land protocol but does not have direct access to the  hardware.  The  X
>        Input Extension devices created by Xwayland ("xwayland-pointer", "xway‐
>        land-keyboard", etc.) map to the Wayland protocol devices, not to phys‐
>        ical devices.
> 
>        These  X  Input  Extension  devices are only visible to other X clients
>        connected to the same Xwayland process. Changing properties on Xwayland
>        devices  only  affects the behavior of those clients. For example, dis‐
>        abling an Xwayland device with xinput does not disable  the  device  in
>        Wayland-native  applications.  Other changes may not have any effect at
>        all.
> 
>        In most instances, using xinput with an Xwayland device  is  indicative
>        of  a  bug  in  a shell script and xinput will print a warning. Use the
>        Wayland Compositor's native device configuration methods instead.

In X11, I don't get the warning. Here is the output when I run the daemon:
```bash
$ sudo ydotoold --socket-path="$HOME/.ydotool_socket" --socket-own="$(id -u):$(id -g)"
[sudo] password for gabriel: 
Socket path: /home/gabriel/.ydotool_socket
Removing old stale socket
Socket permission: 0600
Socket ownership: UID=1000, GID=1000
READY
```


## References:

1. [The comment from @Rinzwind
 where I first found out about `ydotool`](https://askubuntu.com/questions/1470593/how-can-i-write-a-program-to-press-keys-such-as-windows-d-in-wayland-repla?noredirect=1#comment2577739_1470593)
1. https://github.com/ReimuNotMoe/ydotool - official repository for `ydotool`
1. [Ask Ubuntu Equivalent to xdotool for Wayland](https://askubuntu.com/a/1299008/327339) - mentions `ydotool`
1. [my answer] Bugs in Wayland, and how to change between the X11 and Wayland window managers in Ubuntu: [Ask Ubuntu: "failed to enable link training" when resuming from suspend](https://askubuntu.com/a/1470563/327339)
1. [my answer] [Ask Ubuntu: How can I add "Show desktop" to the GNOME dash or Ubuntu Dock?](https://askubuntu.com/a/1109490/327339)
1. [my answer] [Get the User ID (UID) and Group ID (GID) for the running user](https://askubuntu.com/a/1472531/327339)
1. Where I learned about `sudo -b`: [Running a program in the background as sudo](https://stackoverflow.com/a/67472605/4561887)
1. Where I learned about the `-f` part of `ps auxf` to graphically show the process hierarchy (previously I just used `ps aux`): [Unix & Linux: How to view the names all child processes spawned by a program](https://unix.stackexchange.com/a/453654/114401)
