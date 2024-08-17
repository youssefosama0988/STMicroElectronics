
#ifndef MAIN_H
#define MAIN_H

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>

#define KBYTE                  1000
#define MBYTE                 (KBYTE*KBYTE)
#define SIZE_OF_HEAP          (16*MBYTE)
#define PAGE                  (4*KBYTE)
#define STRUCT_SIZE            24
#define OFFSET                 4
#define PROGRAM_BRK_INIT      (128*KBYTE)

typedef struct block{
	
	struct block *previous_free_block;
	struct block *next_free_block;
	int length;
	
}block_t;


void *HmmAlloc(size_t size);
void HmmFree(void *ptr);

void InsertBlockAfter(block_t *block_before , block_t *new_block , int data);
void InsertBlockAtEnd(block_t *head , block_t *new_block , int data);
void DeleteBlock(block_t *block);
block_t* Split(block_t *main_block , int split_value);
block_t* SearchSize(block_t *head ,int required);
block_t* SearchAddress(block_t *head , block_t *new_block);
void Merge(block_t *new_block , int data);
block_t* GetLastBlock(block_t *head );
void DisplayBlocks(block_t *head);

#endif
