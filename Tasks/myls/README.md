# myls
  myls is a custom implementation of the Unix/Linux ls command, designed to provide enhanced functionality with the following options: **-l, -a, -t, -u, -c, -i, -f, -d and -1.**
## Features
- **Long format:** Detailed information about each file, including permissions, number of links, owner, group, size, and modification date.
- **Inclusion of hidden files:** Lists files that start with a dot.
- **Sorting capabilities:** Sort files based on modification time, access time, or status change time.
- **Display inode numbers:** Shows the inode number for each file.
- **Flexible output options:** Control the sorting and format of the displayed output.
- **Support Listing more than One Directory**

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
## Output:
### Dynamic Listing
![dynamic_listing](https://github.com/user-attachments/assets/16d1941c-341d-4524-93c2-95843cd13585)
<br>
### Long Format
![long_format](https://github.com/user-attachments/assets/c017858c-ff02-43d4-a362-f044f8682d72)
<br>
### Display All Directories
![sort_All](https://github.com/user-attachments/assets/bc87fa4a-3a1a-48d5-8493-5762bfb286bb)
<br>

### Sorting by Modification Time
![sort_by_Mtime](https://github.com/user-attachments/assets/09e7ec65-47f1-4377-b242-954c5dc83de5)
<br>
### Show Inode & Display more than one Dir.
![inode MultipleListing](https://github.com/user-attachments/assets/e667e84d-aa2a-41ee-b468-658694a9668e)
<br>
### One entry per line
![print_OneLine](https://github.com/user-attachments/assets/c744d706-ed18-44dc-a6e9-0fedc55f7b5f)










