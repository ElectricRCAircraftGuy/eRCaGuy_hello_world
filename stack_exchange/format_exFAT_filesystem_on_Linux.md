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

# UPDATE: THIS DOCUMENT ENDED UP BECOMING THESE 2 THINGS:
1. https://gabrielstaples.com/exfat-clusters/
1. https://unix.stackexchange.com/a/746786/114401

-->

## How to format an exFAT filesystem on Linux with the desired cluster size to tune your selection along the tradeoff curve between speed and disk usage

Setting the cluster size is really important, it turns out, when formatting exFAT, as it significantly affects the speed and disk usage (see the plots I made, below). 

Read more here:
1. My answer: [Is it best to reformat the hard drive to exFAT using 512kb chunk, or smaller or bigger chunks?](https://superuser.com/a/1785239/425838)
1. My website article: https://gabrielstaples.com/exfat-clusters/

If you use the Gnome Disks utility on Linux to format the exFAT drive, it chooses the cluster size for you, probably according to Microsoft's default values here: [Support.Microsoft.com: Default cluster size for NTFS, FAT, and exFAT](https://support.microsoft.com/en-us/topic/default-cluster-size-for-ntfs-fat-and-exfat-9772e6f1-e31a-00d7-e18f-73169155af95):

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

So, here's **how to manually set your own cluster size**. I recommend a cluster size of **8 KiB**. The below information is a summary from my website here: https://gabrielstaples.com/exfat-clusters/#formatting-an-exfat-drive-on-linux-ubuntu:

1. First, use gparted to prepare a partition. Format it to anything initially--ex: ext4. We'll change that later from the command line.
1. Install dependencies. See: https://itsfoss.com/format-exfat-linux/
    ```bash
    sudo apt update 
    sudo apt install exfat-fuse exfat-utils  # for Ubuntu 20.04 and earlier
    sudo apt install exfat-fuse exfatprogs   # for Ubuntu 22.04 and later
    ```
1. Ensure your partition you are about to format is NOT mounted:
    ```bash
    sudo umount /media/your_name/your_disk
    ```
1. Format your partition as exFAT, setting the cluster size to 8 KiB, assuming your sector size is 512 bytes:
    ```bash
    time sudo mkexfatfs -n "my_exFAT" -s 16 /dev/sda999    #   8 KiB clusters (0.698 sec) <=== WHAT I USE AND RECOMMEND: 8 KiB clusters
    ```

    This just takes a few seconds.
1. Done!


If you'd like to use other cluster sizes, here are some more examples. YOu can use any power of 2 after `-s`, for a max cluster size of 32 MiB:

```bash
# Set the name after `-n` to whatever you want too. `-s` specifies how many
# sectors to use per cluster. Assuming you have 512 byte sectors, the following
# cluster size comments are accurate.
#
#                                                       cluster size  (format time)
#                                                       ----------    -------------
time sudo mkexfatfs -n "my_exFAT" -s 1 /dev/sda999     #   0.5 KiB (512 byte) 
                                                     #     clusters (10 sec)
time sudo mkexfatfs -n "my_exFAT" -s 8 /dev/sda999     #   4 KiB clusters (1.340 sec)
time sudo mkexfatfs -n "my_exFAT" -s 16 /dev/sda999    #   8 KiB clusters (0.698 sec) <=== WHAT I USE AND RECOMMEND: 8 KiB clusters
time sudo mkexfatfs -n "my_exFAT" -s 64 /dev/sda999    #  32 KiB clusters (0.230 sec)
time sudo mkexfatfs -n "my_exFAT" -s 256 /dev/sda999   # 128 KiB clusters (0.075 sec)
time sudo mkexfatfs -n "my_exFAT" -s 65536 /dev/sda999 # 32 MiB clusters (0.120 sec) [absolute max cluster size allowed!]
```

For details and plots on how cluster size affects speed and disk usage, see my links above.

Here are the tradeoff curves of cluster size vs speed and disk usage, as I first presented on my website here: https://gabrielstaples.com/exfat-clusters/

[![enter image description here][1]][1]




  [1]: https://i.stack.imgur.com/j1KyA.png
