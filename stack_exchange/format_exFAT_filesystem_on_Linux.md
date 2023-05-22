<!--
GS
22 May 2023
https://unix.stackexchange.com/questions/61209/create-and-format-exfat-partition-from-linux

ADD ANSWER HERE!: https://unix.stackexchange.com/questions/61209/create-and-format-exfat-partition-from-linux

gparted: create partition

`sudo apt install` stuff: https://itsfoss.com/format-exfat-linux/

```bash
sudo umount /media/gabriel/my_exFAT
# each sector is 512 bytes! gparted: View -> Device Information -> see "Sector size"
# https://manpages.ubuntu.com/manpages/bionic/man8/mkexfatfs.8.html
sudo mkexfatfs -n "my_exFAT" -s 8 /dev/sda1  # `-s 8` -> 4 KiB cluster size!
```
-->


## Which filesystem to use for Windows, Mac, and Linux?

First off, let's make sure you actually want to to be formatting your filesystem as **exFAT**. Here's what I recommend you format your filesystem to for Linux, Windows, and Mac.

1. Single OS use:
    1. For **Linux use only**, including on external hard drives, format your filesystem as **ext4** via the gparted GUI. EXT4 is a Linux file format. This is what I use the most, even on external hard drives, since I'm a heavy Linux user.
        1. For optional encryption, use LUKS, which can be configured through the Gnome Disks GUI.
    1. For **Windows use only**, format the filesystem as **ntfs** via the gparted GUI.
        1. For optional encryption, use a [VeraCrypt](https://www.veracrypt.fr/en/Downloads.html) container stored on the NTFS partition.
    1. For **MacOS use only**, format the filesystem as **apfs** (Apple Filesystem). This must be done on a Mac via the Mac Disks utility. There are several format options available in this utility, as shown here, including "APFS", "APFS (Encrypted)", "APFS (Case-sensitive)", "APFS (Case-sensitive, Encrypted)":
        [![enter image description here][1]][1]

        1. There is currently no fully-functional APFS open source implementation available on any operating system today, that I am aware of, as Apple wants. They like to have their equipment be as incompatible as possible.
        1. For optional encryption, turn on the File Vault encryption inside the MacOS security settings.
1. Shared OS use:
    1. For sharing files between **Linux and Windows**, use **ntfs**, formatted via the gparted GUI. NTFS is a Microsoft file format, but Linux, such as Linux Ubuntu, fully supports both reading and writing to it with no additional configuration.
        1. For optional encryption, use a [VeraCrypt](https://www.veracrypt.fr/en/Downloads.html) container stored on the NTFS partition.
    1. For sharing files between **Mac and Windows**, **Linux and Mac**, **Windows and Mac**, or **Windows, Mac, and Linux**, use **exFAT**, formatted via the command-line on Linux, as I show below. 
        1. ExFAT is a Microsoft file format, but its specifications have apparently been fully released, and Windows, Mac, and Linux all support reading and writing to it without additional configuration on any system. Both Mac and Windows have exFAT as a format option in their disk GUI utilities as well, and Linux supports formatting to this type as well via the Gnome Disks utility and the command line, which I show below. You can also use FAT32, but it is much more limited than exFAT, particular with its 4 GiB maximum file size limit, as shown in the "Limits" table [from Microsoft here](https://learn.microsoft.com/en-us/windows/win32/fileio/filesystem-functionality-comparison), so I strongly recommend exFAT instead.
        1. For optional encryption, use a [VeraCrypt](https://www.veracrypt.fr/en/Downloads.html) container stored on the exFAT partition.


## How to create and format an exFAT partition on Linux

#### Quick summary
1. 


## Speed tests, based on exFAT cluster size

```bash
# NB: **creation** speed goes way faster for larger clusters too! The times
# below are for creating an exFAT file system of these cluster sizes on a 500
# GB Western Digital Blue (rated 3500 MB/sec) SSD.
#
# When using a file manager to right click and create a new folder, there was a
# very noticeable lag when I did it with a cluster size of 0.5 KiB. 

time sudo mkexfatfs -n "my_exFAT" -s 1 /dev/sda1     #   0.5 KiB (512 byte) 
                                                         #     clusters    (10 sec)
time sudo mkexfatfs -n "my_exFAT" -s 8 /dev/sda1     #   4 KiB clusters (1.340 sec)
time sudo mkexfatfs -n "my_exFAT" -s 16 /dev/sda1    #   8 KiB clusters (0.698 sec)
time sudo mkexfatfs -n "my_exFAT" -s 64 /dev/sda1    #  32 KiB clusters (0.230 sec)
time sudo mkexfatfs -n "my_exFAT" -s 256 /dev/sda1   # 128 KiB clusters (0.075 sec)
time sudo mkexfatfs -n "my_exFAT" -s 65536 /dev/sda1 # 32 MiB clusters (0.120 sec) 
                                                         #   [absolute max cluster size allowed!]
```

A "cluster" is the smallest chunk of memory possible to be used by the file system. So, if a cluster is 4 KiB, for instance, and your file is only **1 byte**, it will still take up a full cluster, or **4 KiB**, on disk. This is what Windows refers to as "Size on disk". In this case, the file "Size" is 1 byte, whereas the "Size on disk" is 4 KiB, or 4096 bytes. See: [Super User: What is the difference between “Size” and “Size on disk?”](https://superuser.com/a/66826/425838).

[![enter image description here][2]][2]


I ran some speed tests by using `rsync` 

```
----------------------------------------------------
0.5 KiB (512 byte) clusters (1 x 512 byte sector)
----------------------------------------------------
exFAT creation time (sec):  10

Write time (sec):   57.566  51.939
Write speed (MB/s): 87.36   96.84
Erase time (sec):   unk     15.015

----------------------------------------------------
4 KiB clusters (8 x 512 byte sectors)
----------------------------------------------------
exFAT creation time (sec):  1.340

Write time (sec):   17.664  14.322  16.296
Write speed (MB/s): 285.36  352.37  309.35
Erase time (sec):   2.061   1.842   1.981

----------------------------------------------------
8 KiB clusters (16 x 512 byte sectors)
----------------------------------------------------
exFAT creation time (sec):  0.698

Write time (sec):   15.138  15.711  13.987
Write speed (MB/s): 333.19  320.87  360.62
Erase time (sec):   1.301   1.111   1.175

----------------------------------------------------
32 KiB clusters (64 x 512 byte sectors)
----------------------------------------------------
exFAT creation time (sec):  0.230

Write time (sec):   13.989  15.317  13.017
Write speed (MB/s): 360.59  329.26  387.60
Erase time (sec):   0.583   0.495   0.546

----------------------------------------------------
128 KiB clusters (256 x 512 byte sectors)
----------------------------------------------------
exFAT creation time (sec):  0.075

Write time (sec):   12.873  13.866  12.202
Write speed (MB/s): 392.01  363.88  413.63
Erase time (sec):   0.396   0.343   0.380

----------------------------------------------------
32 MiB clusters (65536 x 512 byte sectors)
----------------------------------------------------
exFAT creation time (sec):  0.120

Write time (sec):   11.544  12.334  11.554
Write speed (MB/s): 437.09  409.12  436.98
Erase time (sec):   0.315   0.360   0.336
```


32 MiB (65536 x 512-byte sectors)
```bash
 time sudo mkexfatfs -n "my_exFAT" -s 65536 /dev/sda1 # 32 MiB clusters (0.075 sec) 
mkexfatfs 1.3.0
Creating... done.
Flushing... done.
File system created successfully.

real    0m0.129s
user    0m0.014s
sys 0m0.048s




$ time rsync --info=progress2 /home/gabriel/Downloads/OSs/Windows/Win10_2004_English_x64.iso /media/gabriel/my_exFAT/
  5,268,953,088 100%  437.09MB/s    0:00:11 (xfr#1, to-chk=0/1)

real    0m11.544s
user    0m2.168s
sys 0m5.686s
$ time rm /media/gabriel/my_exFAT/Win10_2004_English_x64.iso 

real    0m0.315s
user    0m0.004s
sys 0m0.305s
$ time rsync --info=progress2 /home/gabriel/Downloads/OSs/Windows/Win10_2004_English_x64.iso /media/gabriel/my_exFAT/
  5,268,953,088 100%  409.12MB/s    0:00:12 (xfr#1, to-chk=0/1)

real    0m12.334s
user    0m2.191s
sys 0m6.609s
$ time rm /media/gabriel/my_exFAT/Win10_2004_English_x64.iso 

real    0m0.360s
user    0m0.001s
sys 0m0.350s
$ time rsync --info=progress2 /home/gabriel/Downloads/OSs/Windows/Win10_2004_English_x64.iso /media/gabriel/my_exFAT/
  5,268,953,088 100%  436.98MB/s    0:00:11 (xfr#1, to-chk=0/1)

real    0m11.554s
user    0m2.306s
sys 0m6.401s
$ time rm /media/gabriel/my_exFAT/Win10_2004_English_x64.iso 

real    0m0.336s
user    0m0.005s
sys 0m0.328s

```




  [1]: https://i.stack.imgur.com/al2Xg.jpg
  [2]: https://i.stack.imgur.com/8hsqy.jpg
