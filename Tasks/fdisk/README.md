## ***FDisk***
fdisk is a custom implementation of the fdisk -l command, which is used to list the disk partitions on a Linux system.
This tool aims to provide similar functionality to the traditional **fdisk -l** command.

## Features
 - Lists all disk partitions and their details.
 - Shows details such as partition start, end, size, and type.
 - Provides a user-friendly output format.
 - Allows for additional options and customizations.

<br>

## Building commands 

```
  git clone repoURL
  gcc fdisk.c -o myfdisk

  /*to run the program*/
  sudo ./myfdisk /dev/sdx       /* Replace /dev/sdX with the appropriate device identifier (e.g., /dev/sda). */
  
```
## Limitations
  - Requires root permissions to access disk device files.

## Example
![Fdisk_Output](https://github.com/user-attachments/assets/7e996b5e-7e12-4652-bab9-dc8627985b96)
