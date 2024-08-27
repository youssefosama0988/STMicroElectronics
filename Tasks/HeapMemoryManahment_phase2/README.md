# *Heap Memory Management*
 This project demonstrates custom heap memory management by replacing the standard library functions **malloc**, **calloc**, **realloc**, and **free** with custom implementations. This can be useful for optimizing memory usage, debugging memory leaks, or experimenting with different memory allocation strategies.
 
## Overview
This project includes implementations of the **malloc**, **calloc**, **realloc**, and **free** functions to manage dynamic memory allocation on the heap. The goal is to provide insight into how memory allocation works under the hood.

## Objectives

   **Understand Custom Memory Management:** Learn how to manage memory allocation and deallocation manually.
   
   **Replace Standard Library Functions:** Override malloc, calloc, realloc, and free to use custom implementations.
   
   **Experiment with Custom Strategies:** Test and debug different memory management techniques.
<br>
## Building commands 
```

  git clone repoURL

  /*to run the test program (main.c include the test). */
  gcc main.c HMM.c LinkedList.c -o hmm
  ./hmm                                 

  gcc -g -fPIC -Wall -shared HMM.c LinkedList.c -o libHmm.so             // command to make the shared library.
  export LD_PRELOAD=`realpath libHmm.so`                                 // using libHmm.so instead of the standard ones.

 /* to run command immediately with the library*/
 LD_PRELOAD=`realpath libHmm.so` command

```
## Output sample of the test program
![Sample](https://github.com/user-attachments/assets/e6fa6533-9ce6-4c97-985d-f4256b7c1035)
---------------

## Flowcharts


![Free](https://github.com/user-attachments/assets/eb8b0c80-3bbb-4470-aa10-bcb0bf8cf0c4)
---------------
<br>
<br>

![Malloc](https://github.com/user-attachments/assets/b176e74d-1242-4675-ac29-b9b9f4574127)
---------------

## Contact

For questions or contributions, please contact **Youssef Osama** at youssefosama789456@gmail.com .
