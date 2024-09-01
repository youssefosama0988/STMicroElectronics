## ***FDisk***
This project is a custom implementation of the 'fdisk -l' command, which is used to list the disk partitions on a Linux system.

## Overview
command-line tool for parsing and displaying partition information from disk images. It supports both **Master Boot Record (MBR)** and **GUID Partition Table (GPT)** partitioning schemes. The tool reads partition tables and provides detailed information about each partition, including type, size, and start/end sectors.

## Features
 - **MBR Parsing:** Handles MBR partition tables, displaying information about primary and extended partitions.
 - **GPT Parsing:** Supports GPT partition tables, showing details for each partition in the GPT.
 - **Logical Partitions:** Supports displaying logical partitions within extended partitions in MBR.
 - Shows details such as partition start, end, size, and type.
 - Provides a user-friendly output format.

<br>

## Building commands 

```
  git clone https://github.com/youssefosama0988/STMicroElectronics/tree/main/Tasks/fdisk
  gcc fdisk.c -o myfdisk

  /*to run the program*/
  sudo ./myfdisk /dev/sdx       /* Replace /dev/sdX with the appropriate device identifier (e.g., /dev/sda). */
  
```
## Limitations
  - Requires root permissions to access disk device files.
  - Unsupported Formats: The program assumes MBR or GPT format and may not handle other types of partitioning schemes.

## Example

MBR example:

![Fdisk_Output](https://github.com/user-attachments/assets/7e996b5e-7e12-4652-bab9-dc8627985b96)

GPT example:

![GPT output](https://github.com/user-attachments/assets/0bbb10a0-e809-4675-bdd2-479abf513a9a)
