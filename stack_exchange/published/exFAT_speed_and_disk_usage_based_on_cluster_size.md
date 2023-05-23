<!--
GS
22 May 2023

My answer: https://superuser.com/a/1785239/425838
-->


# UPDATE: THIS DOCUMENT ENDED UP BECOMING THESE 2 THINGS:
1. https://gabrielstaples.com/exfat-clusters/
1. https://unix.stackexchange.com/a/746786/114401



------------
----
----


## exFAT speed and disk usage based on cluster size

I just spent the day testing and plotting, and it turns out that exFAT cluster size has a *significant* (I mean: huuuuge!) effect on both _speed_ and _disk usage_ for a given application. 

Check out this data I collected and plotted:






I'm not answering the OPs question about "recording HDTV programs". I'm answering for people with lots of small files, including doing a full disk backup, as they will certainly land on this page too.

---

_I'd choose the smallest allocation unit possible if you have a lot of small files. This avoids wasted space for tiny files._ Ex: use 4 KiB allocation unit size on exFAT instead of 128 KiB.

I just backed up **74 GB** of data from an Apple APFS filesystem onto an external SSD with an exFAT filesystem with **128 KB allocation unit sizes** (the default apparently when formatting to exFAT using Gnome Disks in Linux Ubuntu), and on the external drive, the **formerly-74 GB** of data on the APFS filesystem now takes up a whopping **194 GB** on the exFAT filesystem! That's nuts! That's **2.62x** more space taken, for nothing!

It's because I have thousands and thousands of tiny files that are, for instance, only a couple hundred *bytes*. On the old drive with the APFS filesystem, those would take up a single **512 byte** cluster, and on the new external drive with the exFAT filesystem, those same 90 byte files take up a whopping **128 KB** cluster, which is `128KiB * 1024 bytes/KiB / 512 bytes` = **256 times larger** storage space required on the exFAT drive for tiny files. Reducing that 128 KiB allocation unit to only 4 KiB, for instance, would take up 128/4 = **32x less space!**


## See also:
1. My answer on how to determine the cluster size of any filesystem you have: [Server Fault: How to find the cluster size of _any_ filesystem, whether NTFS, Apple APFS, ext4, ext3, FAT, exFAT, etc.](https://serverfault.com/a/1131628/357116)
1. [REALLY USEFUL] [Support.Microsoft.com: Default cluster size for NTFS, FAT, and exFAT](https://support.microsoft.com/en-us/topic/default-cluster-size-for-ntfs-fat-and-exfat-9772e6f1-e31a-00d7-e18f-73169155af95):

    > #### Default cluster sizes for exFAT
    >
    > The following table describes the default cluster sizes for exFAT.
    > 
    > | Volume size | Windows 7, Windows Server 2008 R2, Windows Server 2008, <br>Windows Vista, Windows Server 2003, Windows XP |
    > | ----------- | ------- |
    > | 7 MB–256 MB | 4 KB |
    > | 256 MB–32 GB | 32 KB |
    > | 32 GB–256 TB | 128 KB |
    > | \> 256 TB | Not supported |


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

