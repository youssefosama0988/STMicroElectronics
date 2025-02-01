# Non-Blocking Wait Alternative

## Objective
Implement a non-blocking wait alternative to the `wait()` system call. should handle all terminated children and print the PID, exit status, and the reason for termination (signal or normal exit).
The application should ensure that no dead child processes become zombies.

## Features
- **Non-blocking wait**: The program handles terminated child processes without blocking the main process, preventing zombie processes.
- **Signal handling**: The program will handle `SIGCHLD` signals to detect and reap child processes asynchronously.

## Setup

1. Clone the repository:
   
       git clone https://github.com/youssefosama0988/STMicroElectronics.git

       cd Tasks/Non-Blocking_wait_syscall


2.Compilation Commands

      gcc -o non_blocking_wait non-blocking_wait.c 

3.Run the program      

      ./non-blocking_wait

## video 
[Watch the video](https://drive.google.com/file/d/1MnwPM1agidKKyPn7cRrF6t0GYj-BTaGP/view?usp=drive_link)


