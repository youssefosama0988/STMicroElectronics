
#ifndef HMM_h
#define HMM_H

#include "LinkedList.h"






#define KBYTE                  1000
#define MBYTE                 (KBYTE*KBYTE)
#define SIZE_OF_HEAP          (16*MBYTE)
#define PAGE                  (4*KBYTE)
#define STRUCT_SIZE            24
#define OFFSET                 4
#define PROGRAM_BRK_INC      (128*KBYTE)





extern int Heap[SIZE_OF_HEAP];
extern void *program_brk;


void *HmmAlloc(size_t size);
void HmmFree(void *ptr);

#endif
