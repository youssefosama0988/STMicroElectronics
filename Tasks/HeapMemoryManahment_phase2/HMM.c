#include "HMM.h"

char Heap[SIZE_OF_HEAP];
void *program_brk = Heap;

void *malloc(size_t size){
	return HmmAlloc(size);
}

void free(void *ptr){
	HmmFree(ptr);
}

void *calloc(size_t nmemb, size_t size){
	return HmmCalloc(nmemb,size);
}

void *realloc(void *ptr, size_t size){
	return HmmRealloc(ptr , size);

}


/*=======================================================================================================================================================*/

void *HmmAlloc(size_t size){
	block_t *head = (block_t *)( (void *)Heap + STRUCT_SIZE );
	block_t *ret;
	
	size = ((size + 7)/8)*8;			//size allignment
	if(size<48){
		size = 2*STRUCT_SIZE;
	}	
	
	/* First Allocation */
	if(program_brk == Heap){
		program_brk += PROGRAM_BRK_INC;	            //increment program_brk by pages with respect to the size of allocation
		/* initialize the first struct */
		((block_t *)Heap) -> previous_free_block = NULL;
		((block_t *)Heap) -> next_free_block = NULL;
		((block_t *)Heap) -> length = SIZE_OF_HEAP;
		
		InsertBlockAtEnd( (block_t *)Heap, head, PROGRAM_BRK_INC-STRUCT_SIZE);	//add Head node
		ret = Split(head , size+OFFSET);					//split func. split the passed block and return pointer to the rest.
		*(int *)head = size+OFFSET;
						
		return (void *)head+OFFSET;						//save the size of the block and return pointer to the available block to use
	}
	
	ret = SearchSize( ((block_t *)Heap) -> next_free_block , size+OFFSET );		//return first block its length >= the required

	/*there is free block to allocate */
	if(NULL != ret){ 						
	
		// if the length of the block = the length of required ----> delete the block from free list , else split it	
		if( ret->length == size+OFFSET || ret -> length <= size+OFFSET+(2*STRUCT_SIZE) ){		
			DeleteBlock(ret);
			*(int *)ret = ret->length;
			
		}
		else{
			Split(ret , size+OFFSET);
			*(int *)ret = size+OFFSET;
		}
		
		return (void *)ret+OFFSET;
	}
	
	/* no free blocks suitable to allocate */
	else{	
		ret = GetLastBlock((block_t *)Heap);
		
		/* case: top of the heap is free block */
		if( ((void *)ret + ret -> length) == program_brk){              
			
			if( program_brk + PROGRAM_BRK_INC > (void *)Heap+SIZE_OF_HEAP){            // check the end of the heap
				/* handle if there is small available size to allocate*/
						/*here*/
				if(program_brk + size < (void *)Heap+SIZE_OF_HEAP){
				
					program_brk = (void *)((void *)Heap+SIZE_OF_HEAP);   //increment the program_brk to the end of heap.
					DeleteBlock(ret);
					InsertBlockAtEnd( (block_t *)Heap, (void *)ret + size + OFFSET , program_brk -  ((void *)ret + size + OFFSET) ); // create new block with the remaining size
					*(int *)ret= size + OFFSET;
					
					return (void *)ret+OFFSET;
				}		
				else{
					//printf("\nEnd of heap\n");
					return NULL;
				}
			}
			
			else {							// available to increase the program_brk
				program_brk += PROGRAM_BRK_INC;
				DeleteBlock(ret);
				InsertBlockAtEnd( (block_t *)Heap, (void *)ret + size + OFFSET , program_brk -  ((void *)ret + size + OFFSET) ); // create new block with the remaining size
				*(int *)ret= size + OFFSET;
				
				return (void *)ret+OFFSET;
			}
		}
	
		/* case top of the heap is allocated block --> increases program_brk and allocate then add the rest in free list */
		else{		
			if( program_brk + PROGRAM_BRK_INC > (void *)Heap+SIZE_OF_HEAP){            // check the end of the heap
				/* handle if there is small available size to allocate*/
						
				if(program_brk + size < (void *)Heap+SIZE_OF_HEAP){
					ret = (block_t *)program_brk;
					program_brk = (void *)((void *)Heap+SIZE_OF_HEAP);   //increment the program_brk to the end of heap.
					InsertBlockAtEnd( (block_t *)Heap, (void *)ret + size + OFFSET , program_brk -  ((void *)ret + size + OFFSET) ); // create new block with the remaining size
					*(int *)ret= size + OFFSET;
					
					return (void *)ret+OFFSET;
				}		
				else{
					//printf("\nEnd of heap\n");
					return NULL;
				}
			}
			else{				
				ret = (block_t *)program_brk;
				program_brk += PROGRAM_BRK_INC;         // increase program brk
				InsertBlockAtEnd( (block_t *)Heap, (void *)ret + size + OFFSET , program_brk -  ((void *)ret + size + OFFSET) ); // create new block with the remaining size
				*(int *)ret= size + OFFSET;
				
				return (void *)ret+OFFSET;
			}
		}
	}
	
}


/*==================================================================================================================================================================*/

void HmmFree(void *ptr){
	int size;
	block_t *block_before;
	block_t *block_after;
	block_t *last_block;
	bool merge_3blocks_condition;
	bool merge_2blocks_condition;
	
	if(NULL == ptr){
		return;
	}
	
	ptr -= OFFSET;
	size = *(int *)ptr;
	/* Search  for the block located before the allocated block */
	block_before = SearchAddress((block_t *)Heap , (block_t *)ptr);
	
	
	if(NULL == block_before){		//no free blocks located before the allocated block 
		
		((block_t *)Heap) -> next_free_block -> previous_free_block = ((block_t *)ptr);
		((block_t *)ptr)  -> previous_free_block = ((block_t *)Heap);
		((block_t *)ptr)  -> next_free_block = ((block_t *)Heap) -> next_free_block;
		((block_t *)Heap) -> next_free_block = (block_t *)ptr;
		
		((block_t *)ptr) -> length = size;
		
	}
	else if(block_before == (block_t *)Heap){
	       block_after = block_before -> next_free_block;
	       
	       if( ((void *)block_after) == ptr+size ){
		       
		       InsertBlockAfter((block_t *)Heap, (block_t *)ptr , size + (block_after -> length));
		       DeleteBlock(block_after);
	       }
	       else{
		       InsertBlockAfter((block_t *)Heap,(block_t *)ptr,size);                  
	       }
       
	}
	
	else{
		block_after = block_before -> next_free_block;
		merge_2blocks_condition = ( ((void *)block_before + block_before -> length) == ptr);  //condition to check if the block_before & new free block contigous or not.
		
		if(NULL == block_after){							//if the block_before is the last free block check if them are contigous or not.
			if(merge_2blocks_condition){
				Merge(block_before , size);
			}
			else{
				InsertBlockAfter(block_before , (block_t *)ptr , size);
			}
		
		}
		else{
			merge_3blocks_condition = ( ((void *)block_before + block_before -> length) == ptr) && ( ((void *)block_after) == ptr+size );
			
			if(merge_3blocks_condition){
				Merge(block_before , size + (block_after -> length));
				DeleteBlock(block_after);
			
			}
			else if(merge_2blocks_condition){
				
				Merge(block_before , size);
			}
			else if( ((void *)block_after) == ptr+size ){
			
				InsertBlockAfter(block_before , (block_t *)ptr , size + (block_after -> length));
				DeleteBlock(block_after);
			}
			else{
				InsertBlockAfter(block_before , (block_t *)ptr , size);				
			}
		}	
		
	
	}
	/*
	last_block = GetLastBlock((block_t *)Heap);
	if(last_block->length > PROGRAM_BRK_DEC + (2*STRUCT_SIZE)){
		last_block->length -= PROGRAM_BRK_DEC;
		program_brk -= PROGRAM_BRK_DEC;
	}
	*/
		
}

/*===============================================================================================================================================================*/

void *HmmCalloc(size_t nmemb, size_t size){
	void *ret;
	ret = HmmAlloc(nmemb * size);
	if(NULL != ret){
		memset(ret , 0 , nmemb * size);
	}

	return ret;
}

/*===============================================================================================================================================================*/

void *HmmRealloc(void *ptr, size_t size){
	block_t *ret=NULL;
	if(0 == size){                  //free
		HmmFree(ptr);
		return NULL;
	}
	else if(NULL == ptr){		//malloc
	
		return HmmAlloc(size);
	}
	else if(0){    			//need to add condition if new size smaller than current size.
	
		Split(ptr,size);
	}
	else{
		/***need to edit***/
		HmmFree(ptr);
		ret = HmmAlloc(size);
		memcpy(ptr,ret,size);
		return ret;
		
	}
}


