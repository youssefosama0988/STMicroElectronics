# myls
myls is a custom implementation of the Unix/Linux ls command, designed to provide enhanced functionality with the following options: -l, -a, -t, -u, -c, -i, -f, -d and -1.
## Features
- **Long format:** Detailed information about each file, including permissions, number of links, owner, group, size, and modification date.
- **Inclusion of hidden files:** Lists files that start with a dot.
- **Sorting capabilities:** Sort files based on modification time, access time, or status change time.
- **Display inode numbers:** Shows the inode number for each file.
- **Flexible output options:** Control the sorting and format of the displayed output.

## Options
- **-l:** Long format. Displays detailed information about each file, including permissions, number of links, owner, group, size, and modification date.
- **-a:** All files. Includes hidden files (those starting with a dot) in the output.
- **-t:** Time sort. Sorts files by modification time, showing the most recently modified files first.
- **-u:** Access time. Sorts files by last access time instead of modification time.
- **-c:** Change time. Sorts files by the last status change time.
- **-i:** Inode. Displays the inode number of each file.
- **-f:** Do not sort. Outputs files as they are found in the directory, without sorting.
- **-d:** Directory. Lists directories themselves, not their contents.
- **-1:** One entry per line. Ensures that each file is displayed on a new line.

## Installation
To install myls, follow these steps:

#### 1-Clone the repository:
```
git clone https://github.com/youssefosama0988/STMicroElectronics/tree/main/Tasks/myls
```

#### 2-Compile the program:
```
gcc -o myls main.c functions.c
```
#### 3-Run the program:
After compiling, you can run myls directly from the terminal.
```
./myls [options] [directory]
```
