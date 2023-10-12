---
published: true  # use "false" while drafting articles just before publishing
title: "Linux sleep modes, saving power while sleeping, RAID vs AHCI, and traveling with your Linux laptop"
tags: 
    - linux
    - computers
    - ubuntu
# date: 1999-12-31
# last_modified_at: 2023-05-05  # updates the "Updated" date at the bottom!
# permalink: /test/
# redirect_from: 
# categories: 
toc: true  # (default for Table of Contents is true)
---

<!--
GS
25 June 2023

Publish on my website directly instead. 
Filename: 2023-06-25-linux-sleep-modes.md
URL: https://gabrielstaples.com/linux-sleep-modes/
-->

_Everything here has been tested in Linux Ubuntu 22.04.2, unless specified otherwise._

If you have an SSD (solid state drive), it is safe and recommended to put your Linux laptop to sleep while traveling with the laptop, such as placing it in a backpack to take it to or from work or school, or on a plane. (If it has the older, spinning HDD [Hard Disk Drive], shut it down completely instead). 

<!--
# When should I put my computer to sleep?

Whenever you want to save power without shutting it down completely, put your computer to sleep. Computers can wake up almost instantly from sleep states (in as little as a few seconds), whereas booting up from the power-off state can take several minutes. 

Putting your computer to sleep is most common while transporting it: ex: to or from work or school, while traveling on a plane, etc. 
You can also put it to sleep just to save power 

If your computer uses an old spinning HDD (Hard Disk Drive), it is better to _shut your computer completely down_ before transporting it, rather than simply put it to sleep. This is to guarantee that the drive won't be spinning or accessing its contents while you are transporting it, because if you drop or bump it or give it a sudden jolt, the spinning disk platter can get damaged by the read/write head if they collide together due to a sudden bump. 
-->


# How do you put your computer to sleep (ie: put it in a suspend state)? 

Putting your computer to sleep, or in the "suspend" state, via either option as explained below both locks the screen _and_ puts it into a low power mode where it can last for dozens of hours (if not a few days) without being charged or plugged in. I use this for transporting the computer to and from work or school, or otherwise while traveling or commuting. 

Here is how to put it to sleep:

1. Option 1: in Ubuntu, click on the icons in the very top-right of the desktop --> click "Power Off/Log Out" --> "Suspend". This puts your computer to sleep. Here are what those menus look like in Ubuntu 22.04:
    
    <a href="https://user-images.githubusercontent.com/6842199/248669329-4f4907ee-2bfa-468a-b17b-126e087fcb52.png">
        <p align="left" width="100%">
            <img width="50%" src="https://user-images.githubusercontent.com/6842199/248669329-4f4907ee-2bfa-468a-b17b-126e087fcb52.png">
        </p>
    </a>

1. Option 2: run this from the command-line:
    ```bash
    # Install dependency for screen lock
    sudo apt update 
    sudo apt install gnome-screensaver

    # put your computer to sleep
    gnome-screensaver-command -l && sudo pm-suspend
    ###
    sudo pm-suspend && gnome-screensaver-command -l  # freezes my laptop! Required hard reboot.
    sudo true && gnome-screensaver-command -l && sudo pm-suspend  # works! my answer: https://askubuntu.com/a/1474754/327339

    # See my answer: https://unix.stackexchange.com/a/749867/114401
    journalctl -n 1000 -e | grep "PM: suspend"


    /////// my one-liner to put computer to sleep--my answer:
    // https://askubuntu.com/a/1474754/327339

    /////// nope! sudo applied to too much
    sudo bash -c "gnome-screensaver-command -l && pm-suspend"
    ```
    References:
    1. lock screen: https://askubuntu.com/a/184732/327339
    1. ([Source where I first learned this](https://learnubuntumate.weebly.com/draining-battery.html)) ////////
    1. /////// https://unix.stackexchange.com/questions/654561/how-do-you-go-to-the-end-of-the-file-in-journalctl
    1. //// my comment: https://askubuntu.com/questions/634620/when-using-and-sudo-on-the-first-command-is-the-second-command-run-as-sudo-t#comment2583648_634630
    1. https://github.com/torvalds/linux/blob/master/Documentation/admin-guide/pm/sleep-states.rst
    1. https://unix.stackexchange.com/a/720602/114401

If your computer hardware supports the `deep` "Suspend-to-RAM" sleep state, my experience tells me it will take 10 to 20 seconds to go to sleep. Otherwise, it may go to a shallower sleep state called `s2idle`, or "Suspend-to-Idle", which all Linux computer support. My experience tells me this could take _up to 2 or so minutes_ to fully go to sleep and turn off the computer fan. I'll explain more on this below. 



My personal experience over the last 5 years tells me that Dell is probably a great way to go if you want a computer that works well with Ubuntu. Apparently they have a partnership (see [here: https://ubuntu.com/dell](https://ubuntu.com/dell) and [here](https://www.techradar.com/news/one-of-the-best-dell-laptops-is-now-ubuntu-2204-certified)), and that may be part of the reason that Dells seem to run Ubuntu well overall.


https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-power

https://unix.stackexchange.com/questions/720514/cannot-write-into-sys-power-mem-sleep-in-fedora-36

https://askubuntu.com/questions/1434729/what-does-this-command-do-echo-deep-sudo-tee-a-sys-power-mem-sleep

AHCI better for battery: https://bugzilla.kernel.org/show_bug.cgi?id=211879#c31

***** https://discussion.fedoraproject.org/t/dell-battery-drained-while-suspended/66514/10

***** https://www.google.com/search?q=linux+power+consumption+s2idle+raid+vs+ahci&sxsrf=APwXEdddVLGjsPg9bis7JM3PJClQtvcbLg%3A1686546944238&ei=AKqGZK6UDvTPkPIPqKCciAU&ved=0ahUKEwiulIj8_Lz_AhX0J0QIHSgQB1EQ4dUDCBA&uact=5&oq=linux+power+consumption+s2idle+raid+vs+ahci&gs_lcp=Cgxnd3Mtd2l6LXNlcnAQAzIFCAAQogQyBQgAEKIEMgUIABCiBDIFCAAQogQyBQgAEKIEOgoIABBHENYEELADOgcIIxCwAhAnOgoIIRCgARDDBBAKOggIIRCgARDDBEoECEEYAFCRDFiwFWCGF2gBcAF4AIABf4gB7AWSAQMzLjSYAQCgAQHAAQHIAQg&sclient=gws-wiz-serp

***** https://www.google.com/search?q=linux+power+consumption+raid+vs+ahci&oq=linux+power+consumption+raid+vs+ahci&aqs=chrome..69i57.5779j0j7&sourceid=chrome&ie=UTF-8


https://learnubuntumate.weebly.com/draining-battery.html


*****+ https://www.kernel.org/doc/Documentation/power/states.txt

*****+++ https://blog.wirelessmoves.com/2022/11/running-ubuntu-linux-on-bleeding-edge-hardware-dell-notebook-with-an-intel-12800h-and-an-nvidia-gpu.html

Researching to write this article took weeks. Here are some of the links I came across and which helped me gain the knowledge I needed to write this:

1. [insert from above]
1. get from here too: https://github.com/ElectricRCAircraftGuy/ElectricRCAircraftGuy.github.io/issues/51#issuecomment-1605764122
