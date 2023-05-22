<!--
GS
22 May 2023
https://unix.stackexchange.com/questions/61209/create-and-format-exfat-partition-from-linux
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


## Speed tests

512 bytes (0.5 KiB) (1 x 512-byte sector)
```bash
$ time rsync --info=progress2 /home/gabriel/Downloads/OSs/Windows/Win10_2004_English_x64.iso /media/gabriel/my_exFAT/
  5,268,953,088 100%   87.36MB/s    0:00:57 (xfr#1, to-chk=0/1)

real    0m57.566s
user    0m3.128s
sys 0m8.873s

$ time rsync --info=progress2 /home/gabriel/Downloads/OSs/Windows/Win10_2004_English_x64.iso /media/gabriel/my_exFAT/
  5,268,953,088 100%   96.84MB/s    0:00:51 (xfr#1, to-chk=0/1)

real    0m51.939s
user    0m3.305s
sys 0m8.844s

$ time rm /media/gabriel/my_exFAT/Win10_2004_English_x64.iso 

real    0m15.015s
user    0m0.002s
sys 0m0.234s



```

4 KiB (8 x 512-byte sectors)
32 KiB (64 x 512-byte sectors)
128 KiB (256 x 512-byte sectors)






  [1]: https://i.stack.imgur.com/al2Xg.jpg
