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

