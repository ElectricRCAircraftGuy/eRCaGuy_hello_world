<!--
GS
22 May 2023

My answer: https://superuser.com/a/1785239/425838
-->

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
