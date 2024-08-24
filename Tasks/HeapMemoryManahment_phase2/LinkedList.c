
#include "LinkedList.h"


/*===============================================================================================================================================================*/

/*** Adding Node after the Passed Node in the first Argument
     add new_block after block_before
***/

void InsertBlockAfter(block_t *block_before , block_t *new_block , int data){

		/* check if the arguments are NULL */
		
		
		if(NULL == block_before -> next_free_block){            //Last free Block 
			
				new_block -> next_free_block     = NULL;				// link the next of the new block to NULL
				new_block -> previous_free_block = block_before;			// link the previous of the new block to the first block
				block_before -> next_free_block  = new_block;				// link the next of the first block to the new block
				
				new_block -> length = data;
		}
		
		else {
			
			(block_before -> next_free_block) -> previous_free_block = new_block;  	// link the previous of the second block to the new block	
			new_block -> next_free_block     = block_before -> next_free_block;	// link the next of the new block to the second block
			new_block -> previous_free_block = block_before;			// link the previous of the new block to the first block
			block_before -> next_free_block  = new_block;				// link the next of the first block to the new block
			
			new_block -> length = data;
		}
					
}
/*===============================================================================================================================================================*/

void InsertBlockAtEnd(block_t *head , block_t *new_block , int data){
	block_t *local_block = head;
	
	if(head == NULL){
		return;
	}
	
	while( NULL != local_block -> next_free_block ){
		local_block = local_block -> next_free_block;
	}
	
	new_block->next_free_block     = NULL;		// link the next of the inserted block by  NULL
	new_block->previous_free_block = local_block;		// link the previous of the inserted block by the last block
	local_block->next_free_block   = new_block;		// link the next of the last block to the inserted block
	
	new_block -> length = data;

}
/*===============================================================================================================================================================*/

block_t* SearchAddress(block_t *head , block_t *new_block){
	
	block_t *local_block = head;
	
	while( local_block < new_block ){
		
		if(NULL == local_block -> next_free_block){
		
			return NULL;
		}
		
		local_block = local_block -> next_free_block;
	}
	return (local_block -> previous_free_block);            // return pointer to the block before the new block

}

/*===============================================================================================================================================================*/

void Merge(block_t *new_block , int data){
	
		new_block -> length += data;
}



/*===============================================================================================================================================================*/

block_t* GetLastBlock(block_t *head ){
	block_t *local_block = head;
	
	while( NULL != local_block -> next_free_block ){
		local_block = local_block -> next_free_block;
	}
	
	return local_block;
}

/*===============================================================================================================================================================*/

void DeleteBlock(block_t *block){

	if( (block -> next_free_block != NULL) && (block -> previous_free_block != NULL) ){
		(block -> next_free_block)-> previous_free_block = block -> previous_free_block;
		(block -> previous_free_block) -> next_free_block = block -> next_free_block;		
	}
	
	else if( block -> previous_free_block == NULL){
		block -> next_free_block -> previous_free_block = NULL;
	}
	
	else if( block -> next_free_block == NULL){
		(block -> previous_free_block) -> next_free_block = NULL;
	}
	
	else{				//
		/*Nothing*/
	}
	
}

/*===============================================================================================================================================================*/

/* search for first fit */
block_t* SearchSize(block_t *head ,int required){
	block_t *local_block = head;
	if(head == NULL){
		return NULL;
	}
	while( (local_block -> length) < required ){
		
		if(NULL == local_block -> next_free_block){
			return NULL;
		}
		
		local_block = local_block -> next_free_block;
	}
	                 
	return local_block;
}

/*===============================================================================================================================================================*/

/***
	use the passed block and return the excess after adding it in the free list
***/
block_t* Split(block_t *main_block , int split_value){
	block_t *ret = (block_t *) ((void *)main_block + split_value);
	
	InsertBlockAfter(main_block ,ret , (main_block -> length) - split_value);
	main_block -> length = split_value;
	DeleteBlock(main_block);
	
	return  ret;
			
}

/*===============================================================================================================================================================*/

void DisplayBlocks(block_t *head){
	block_t *local_block = head;
	int counter = 1;
	
	while(NULL != local_block){
		
		printf("Block number: %i\n" , counter++);
		printf("    Address = %i \t length = %i\n" , (block_t *)local_block , local_block -> length);
		printf("\n");		
		local_block = local_block -> next_free_block;
	}
	printf("-----------------\n");		
}

/*===============================================================================================================================================================*/


