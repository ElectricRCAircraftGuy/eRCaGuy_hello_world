<!--
GS
4 June 2023

https://askubuntu.com/q/1470593/327339
https://askubuntu.com/questions/1470593/how-can-i-write-a-program-to-press-keys-such-as-windows-d-in-wayland-repla?noredirect=1#comment2577739_1470593

https://github.com/ReimuNotMoe/ydotool
https://askubuntu.com/a/1299008/327339
https://askubuntu.com/questions/903532/how-can-i-add-show-desktop-to-the-gnome-dash-or-ubuntu-dock/1109490#1109490
-->


## `ydotool` works well in both X11 _and_ Wayland to press any keys, including <kbd>Windows</kbd> + <kbd>D</kbd>


## 1. Build and install it:

_Tested on Ubuntu 22.04.2 with both the X11 and Wayland window managers (for how to change between the two, see my notes and screenshot [in my answer here](https://askubuntu.com/a/1109490/327339))._

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

```bash
# in one terminal, start the required background daemon process as root, but
# setting its socket file to be accessible by your main user withOUT `sudo`
sudo ydotoold --socket-path="$HOME/.ydotool_socket" --socket-own="$(id -u):$(id -g)"

# In another terminal, send a signal to this running background daemon via the
# open socket inter-process-communication (IPC) pseudo-file. Here, we send the
# Windows + D shortcut key:
#
# Windows + D press and release: window toggle: this hides all windows.
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0
```

That's it! 

Manually press <kbd>Windows</kbd> + <kbd>D</kbd> now to show all windows again so you can see your terminal. 

Even better: this time, let's have it press the keys to **hide all windows, wait 2 seconds, and then** press the keys to **show all windows again:**
```bash
# Note: copy and paste all 3 lines at once:
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0; \
    sleep 2; \
    YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0
```

Voila! I'm so happy I got this working! I now have a viable means of getting my ["show desktop"](https://askubuntu.com/a/1109490/327339) button to work again once I am forced to use Wayland, and once it [is less buggy](https://askubuntu.com/a/1470563/327339) and actually functions right.


## What do keycodes `125:1 32:1 32:0 125:0` mean?

```bash
######## do bug report: 1) help menu only shows if you properly connect to the server, 2) what does the stuff below mean? about xwayland server?
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key -h
```


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


## 


Run this again to show all windows:
```bash
# Windows + D press and release: window toggle: this shows all windows.
YDOTOOL_SOCKET="$HOME/.ydotool_socket" ydotool key 125:1 32:1 32:0 125:0
```


```bash
sudo ./ydotoold

# in another:
#######
# ./ydotool key --clearmodifiers Super+d
YDOTOOL_SOCKET="/tmp/.ydotool_socket" sudo ./ydotool key Super+d

# help menu
YDOTOOL_SOCKET="/tmp/.ydotool_socket" sudo ./ydotool key -h

# Windows + D press and release
YDOTOOL_SOCKET="/tmp/.ydotool_socket" sudo ./ydotool key 125:1 32:1 32:0 125:0

# see all keycodes (the help menu above told me about this file!)
subl /usr/include/linux/input-event-codes.h


# to avoid using `sudo`, change permissions!
# TODO: just add yourself to the group instead--or make your user the owner! Do NOT give everyone permissions!
sudo chmod 666 /tmp/.ydotool_socket
YDOTOOL_SOCKET="/tmp/.ydotool_socket" ./ydotool key 125:1 32:1 32:0 125:0

sudo chown gabriel /tmp/.ydotool_socket
sudo chown "$USER" /tmp/.ydotool_socket  # better
YDOTOOL_SOCKET="/tmp/.ydotool_socket" ./ydotool key 125:1 32:1 32:0 125:0

```


## References:

1. [The comment from @Rinzwind
 where I first found out about `ydotool`](https://askubuntu.com/questions/1470593/how-can-i-write-a-program-to-press-keys-such-as-windows-d-in-wayland-repla?noredirect=1#comment2577739_1470593)
1. https://github.com/ReimuNotMoe/ydotool - official repository for `ydotool`
1. [Ask Ubuntu Equivalent to xdotool for Wayland](https://askubuntu.com/a/1299008/327339) - mentions `ydotool`
1. [my answer] [Ask Ubuntu: How can I add "Show desktop" to the GNOME dash or Ubuntu Dock?](https://askubuntu.com/a/1109490/327339)
1. [my answer] [Get the User ID (UID) and Group ID (GID) for the running user](https://askubuntu.com/a/1472531/327339)
