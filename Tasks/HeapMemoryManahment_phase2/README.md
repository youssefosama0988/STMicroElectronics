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

  git clone https://github.com/youssefosama0988/STMicroElectronics/edit/main/Tasks/HeapMemoryManahment_phase2

  /*to run the test program (main.c include the test). */
  gcc main.c HMM.c LinkedList.c -o hmm
  ./hmm                                 

  gcc -g -fPIC -Wall -shared HMM.c LinkedList.c -o libHmm.so             // command to make the shared library.
  export LD_PRELOAD=`realpath libHmm.so`                                 // using libHmm.so instead of the standard ones.

 /* to run command immediately with the library*/
 LD_PRELOAD=`realpath libHmm.so` command

```
### Heap Allocation Functions:
---------------------------------
 - **HmmAlloc(size_t size):** Allocates memory by finding a suitable block or expanding the heap if necessary.
 - **HmmFree(void *ptr):*** Frees a previously allocated block and merges adjacent free blocks if possible.
 - **HmmCalloc(size_t nmemb, size_t size):** Allocates and initializes memory to zero.
 - **HmmRealloc(void *ptr, size_t size):*** Resizes an allocated block, copying data if necessary.
   
### Linked List Management Functions (LinkedList.c):
----------------------------------
- **InsertBlockAfter(block_t *block_before, block_t *new_block, int data):****  Inserts a new block into the free list after a specified block.
- **InsertBlockAtEnd(block_t *head, block_t *new_block, int data):**** Inserts a new block at the end of the free list.
- **SearchAddress(block_t *head, block_t *new_block):**** Searches for the block preceding a given block.
- **Merge(block_t *new_block, int data):*** Merges adjacent free blocks.
- **GetLastBlock(block_t *head):*** Retrieves the last block in the free list.
- **DeleteBlock(block_t *block):*** Removes a block from the free list.
- **SearchSize(block_t *head, int required):*** Finds a free block of sufficient size.
- **Split(block_t *main_block, int split_value):*** Splits a block into two, adjusting the sizes accordingly.
- **DisplayBlocks(block_t *head):*** Displays information about all blocks in the free list.
  <br>
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
