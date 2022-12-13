<!--
https://askubuntu.com/q/103915/327339
GS: my answer here now: https://askubuntu.com/a/1445347/327339
-->


> I need a step-by-step, simple and easy way to configure swappiness.

I'd like to expound upon the answers already here by adding: 

1. A very concise summary of how to change the swappiness.
1. Some quotes from the latest Linux kernel source code ([see here for how to download it if interested](https://unix.stackexchange.com/a/728275/114401)) on what "swappiness" really means, and what its ranges really are.

So, here it goes:


## 1. How to configure swappiness

```bash
# read current swappiness setting
sysctl vm.swappiness
# or (same thing)
cat /proc/sys/vm/swappiness

# change setting to zero
sudo sysctl vm.swappiness=0
```

The above commands are not persistent across reboots. To make the setting persistent, you need to use `sudo` and edit the file at `/etc/sysctl.conf` to add your desired swappiness setting to the end of it. Example:

```bash
# edit the file with the `nano` editor
sudo nano /etc/sysctl.conf
```

Add this to the end of "/etc/sysctl.conf":
```bash
# my custom swappiness setting
vm.swappiness=0
```

If you choose to _only_ edit that file to set your custom `swappiness` setting, rather than setting it with `sudo sysctl vm.swappiness=0`, then to activate your new setting as set in the file, you will need to either reboot _or_ call the following command to reload the config file:
```bash
# reload just the "/etc/sysctl.conf" config file
sudo sysctl --load

# or: from `man sysctl`:
#
#       Load settings from all system configuration files.
#       /run/sysctl.d/*.conf
#       /etc/sysctl.d/*.conf
#       /usr/local/lib/sysctl.d/*.conf
#       /usr/lib/sysctl.d/*.conf
#       /lib/sysctl.d/*.conf
#       /etc/sysctl.conf
sudo sysctl --system
```

At the end of running either of the above commands, the terminal will print this to stdout:

> vm.swappiness = 0

To see what your current settings are in `/etc/sysctl.conf`:
```bash
cat /etc/sysctl.conf
```


## 2. What is swappiness, straight from the Linux kernel developers' mouths

Download the Linux source code yourself by following my instructions here: [_Where_ and _how_ to get the official Linux kernel source code](https://unix.stackexchange.com/a/728275/114401).

As shown in the Linux Stable repo by `git blame Documentation/admin-guide/sysctl/vm.rst`, this documentation was written by Peter W Morreale, Mauro Carvalho Chehab, and Johannes Weiner (see [the kernel source code here](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/Documentation/admin-guide/sysctl/vm.rst?h=v6.0.12#n889)) (emphasis added): 

> swappiness
> ==========
> 
> This control is used to define the rough relative IO cost of swapping
> and filesystem paging, as a value between **0 and 200**. At 100, the VM
> assumes equal IO cost and will thus apply memory pressure to the page
> cache and swap-backed pages equally; lower values signify more
> expensive swap IO, higher values indicates cheaper.
> 
> Keep in mind that filesystem IO patterns under memory pressure tend to
> be more efficient than swap's random IO. An optimal value will require
> experimentation and will also be workload-dependent.
> 
> The default value is 60.
> 
> For in-memory swap, like zram or zswap, as well as hybrid setups that
> have swap on faster devices than the filesystem, values beyond 100 can
> be considered. For example, if the random IO against the swap device
> is on average 2x faster than IO from the filesystem, swappiness should
> be 133 (x + 2x = 200, 2x = 133.33).
> 
> At 0, the kernel will not initiate swap until the amount of free and
> file-backed pages is less than the high watermark in a zone.

So, values do _not_ range between 0 and 100 anymore. As of [this commit hash c843966c556d7](https://github.com/torvalds/linux/commit/c843966c556d7#diff-aadbd4fa4257439a8ad36840a4a7c06ce1745a0707f9fe945c14b2fb8b11b0e6R835) on Jun 3, 2020, the value now ranges from 0 to 200.

The [commit hash 497a6c1b09902b22ceccc0f25ba4dd623e1ddb7d right before that](https://github.com/torvalds/linux/blob/497a6c1b09902b22ceccc0f25ba4dd623e1ddb7d/Documentation/admin-guide/sysctl/vm.rst) stated this instead:

> swappiness
> ==========
> 
> This control is used to define how aggressive the kernel will swap
> memory pages.  Higher values will increase aggressiveness, lower values
> decrease the amount of swap.  A value of 0 instructs the kernel not to
> initiate swap until the amount of free and file-backed pages is less
> than the high water mark in a zone.
> 
> The default value is 60.


## Which swappiness should I use?

I highly recommend `vm.swappiness=0`! It makes my machine run soooo much better. From my anecdote [in my answer here](https://unix.stackexchange.com/a/728278/114401): 

> I have found that setting swappiness to 0 significantly improves the performance of my system which has 32 GB RAM, a 64 GB swap file on a high-speed m.2 SSD, and which is continually running out of RAM. 
> 
> With swappiness set to the default of 60, I'd regularly get 1 to 2 minute lockup periods while `kswapd0` is running (as shown by `top`) to try to swap memory for some memory hog application like Chrome, Slack, Eclipse, or Google Meet (within Chrome). I'd start to get these lockups at 80% full RAM. The computer would be _completely unusable_ during this time--unable even for me to type into a terminal or click on a menu. 
> 
> Setting swappiness to 0 _significantly helped!_. I started not getting really high CPU usage until 90% RAM full, swap space would still get used plenty--but more efficiently, and when my RAM did get almost full my computer would become very sluggish, but still barely usable rather than completely unusable!
> 
> See some of my symptoms here, which I originally thought were due to a bug in Google Meet, but now think were due to memory swap making my computer slow: https://github.com/ElectricRCAircraftGuy/bug_reports/issues/3#issue-1177137900

On my system: 
- With `vm.swappiness=60`, I'd see 1 to 2 minutes of 100% CPU lockup starting at about 79% RAM usage, every 4 to 6 minutes, forever. This was particularly exacerbated and prominent [when using Google Meet](https://github.com/ElectricRCAircraftGuy/bug_reports/issues/3#issue-1177137900).
- With `vm.swappiness=0`, that wouldn't happen. I'd be fine at 80% RAM usage, and would start to see major sluggishness, but not total lockup like before, by 90% RAM usage.
    - Even with swappiness set to 0, I'd see some usage (a few MB) of swap used as early as 0 to 3% of RAM used, and I'd have heavy swap usage by 80% to 90% RAM used.


## References:
1. https://linuxize.com/post/how-to-change-the-swappiness-value-in-linux/ - where I learned most of the sysctl cmds above
1. https://www.cyberciti.biz/faq/reload-sysctl-conf-on-linux-using-sysctl/ - where I learned the `sysctl --system` cmd above


## Related:

1. [`kswapd0` is taking a lot of cpu](https://askubuntu.com/a/530661/327339) - useful, but this quote is totally wrong though:

    > where 0 is the percent left out of 100 at which SWAP should be used (when you have 0% RAM left, SWAP will start taking in data).
