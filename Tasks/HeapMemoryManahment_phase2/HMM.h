
#ifndef HMM_h
#define HMM_H

#include "LinkedList.h"
#include <string.h>


/*---------------Macros----------------------*/

#define KBYTE                  1024
#define MBYTE                 (KBYTE*KBYTE)
#define SIZE_OF_HEAP          (512*MBYTE)
#define PAGE                  (4*KBYTE)
#define STRUCT_SIZE            24
#define OFFSET                 8
#define PROGRAM_BRK_INC      (136*KBYTE)
#define PROGRAM_BRK_DEC      (128*KBYTE)



/*-----------Variables Declarations-------------*/

extern char Heap[SIZE_OF_HEAP];
extern void *program_brk;

/* ----------Functions Declarations------------*/
void *HmmAlloc(size_t size);

void HmmFree(void *ptr);

void *HmmCalloc(size_t nmemb, size_t size);

void *HmmRealloc(void *ptr, size_t size);

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);


#endif
