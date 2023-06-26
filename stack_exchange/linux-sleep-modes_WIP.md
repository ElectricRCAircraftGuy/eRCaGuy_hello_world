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
