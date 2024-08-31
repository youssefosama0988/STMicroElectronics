## FDisk
fdisk is a custom implementation of the fdisk -l command, which is used to list the disk partitions on a Linux system.
This tool aims to provide similar functionality to the traditional fdisk -l command.

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
  sudo ./myfdisk /dev/sda       /* /dev/sda for example*/
  
```
## Limitations
  - Requires root permissions to access disk device files.

## Example
