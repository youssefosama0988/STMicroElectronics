
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/*------------------------*/
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>


/*-----------Variables Declarations-------------*/

typedef struct block{
	
	struct block *previous_free_block;
	struct block *next_free_block;
	int length;
	
}block_t;

/* ----------Functions Declarations------------*/

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
