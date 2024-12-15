# Real-Time Signal Sender/Receiver Application

## Overview
This project implements a **Sender and Receiver application** using **real-time signals** in Linux. The application demonstrates signal communication and signal handling with additional data using `sigqueue()`.

## Core Functionality
Key features implemented in `sender.c` and `receiver.c`:

### Sender (`sender.c`)
- Creates and sends a real-time signal with a payload using `sigqueue()` to the receiver process.

### Receiver (`receiver.c`)
- Uses `sigaction()` with the `SA_SIGINFO` flag to receive signals and access `sigval`.
- Acts differently based on the payload received:
  - `0`: Terminate the application.
  - `1`: Trigger a core dump.
  - Other values: Log and continue execution

---

## Features
- Real-time signal communication using `sigqueue()`.
- Controlled termination of the receiver application based on signal data.
- Signal handling demonstrating custom payloads in signals (`union sigval`).
- Error handling with real-time signals (`SIGRTMIN` - `SIGRTMAX`).

---


## Setup Instructions
Follow these steps to compile and set up the Sender and Receiver application.

1. **Clone the repository**:
   Clone or download the project code from the repository (if shared via GitHub, etc.).

2. **Compile the Sender and Receiver**:  
   ```bash
   gcc -o sender sender.c
   gcc -o recv reciever.c 
   ```
3. **run the Receiver**:  
   ```bash
     ./recv
   ```
4. **get recv PID**:  
   ```bash
     ps -a   // and copy the PID of recv
   ```
5. **run the sender**:  
   ```bash
     ./sender <PID> <value>
   ```
6. **Expected Behavior**:  
   - When the value `0` is sent, the receiver will terminate.
   - When the value `1` is sent, the receiver will generate a core dump.
   - Otherwise, the receiver will simply continue running.

---
## Video 

[Watch the Demo Video](https://drive.google.com/file/d/1lE4vWRkwv06BHYdIBw2Qlit8OHMnpPm4/view?usp=sharing)


     
