#include "main.h"

int Heap[SIZE_OF_HEAP];
void *program_brk = Heap;

#define NUM_ALLOCS 10000
#define MAX_SIZE 10240
#define MAX_ITERATIONS 1000000

void random_alloc_free_test() {
    srand((unsigned int)time(NULL));
    
    void* pointers[NUM_ALLOCS] = {NULL};
    
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        int index = rand() % NUM_ALLOCS;
        if (pointers[index] == NULL) {
            // Allocate memory
            size_t size = (size_t)(rand() % MAX_SIZE) + 1;
            pointers[index] = HmmAlloc(size);
            if (pointers[index] != NULL) {
                printf("Allocated memory of size %zu at address %p\n", size, pointers[index]);
            } else {
                fprintf(stderr, "Allocation failed for size %zu\n", size);
            }
        } else {
            // Free memory
            printf("Freeing memory at address %p\n", pointers[index]);
            HmmFree(pointers[index]);
            pointers[index] = NULL;
        }
    }
    
    // Free remaining allocated memory
    for (int i = 0; i < NUM_ALLOCS; ++i) {
        if (pointers[i] != NULL) {
            printf("Freeing remaining memory at address %p\n", pointers[i]);
            HmmFree(pointers[i]);
            pointers[i] = NULL;
        }
    }
}

int main() {
    printf("Starting random allocation and deallocation test...\n");
    random_alloc_free_test();
    printf("Test complete.\n");
    return 0;
}

void *HmmAlloc(size_t size){
	block_t *head = (block_t *)( (void *)Heap + STRUCT_SIZE );
	block_t *ret;
	if(size<50){
		size += STRUCT_SIZE;
	}	
	/* First Allocation */
	if(program_brk == Heap){
		program_brk += PROGRAM_BRK_INIT;            //increment program_brk by pages with respect to the size of allocation
		/* initialize the first struct */
		((block_t *)Heap) -> previous_free_block = NULL;
		((block_t *)Heap) -> next_free_block = NULL;
		((block_t *)Heap) -> length = SIZE_OF_HEAP;
		
		InsertBlockAtEnd( (block_t *)Heap, head, PROGRAM_BRK_INIT); //add Head node
		ret = Split(head , size+OFFSET);			//split func. split the passed block and return pointer to the rest.
		*(int *)head = size+OFFSET;
						
		return (void *)head+OFFSET;				//save the size of the block and return pointer to the available block to use
	}
	
	ret = SearchSize( ((block_t *)Heap) -> next_free_block , size+OFFSET );		//return first block its length >= the required

	/*there is free block to allocate */
	if(NULL != ret){ 						
		if(ret -> length <= size+OFFSET+STRUCT_SIZE ){		// if the length of the block = the length of required ----> delete the block from free list , else split it
			DeleteBlock(ret);
			
		}
		else{
			Split(ret , size+OFFSET);
		}
		
		*(int *)ret = size+OFFSET;
		
		return (void *)ret+OFFSET;
	}
	
	/* no free blocks suitable to allocate */
	else{	
		ret = GetLastBlock((block_t *)Heap);
		
		/* case: top of the heap is free block */
		if( ((void *)ret + ret -> length) == program_brk){              
			
			if( (program_brk + ( (size/PAGE) + 1)*PAGE) >= (void *)Heap+SIZE_OF_HEAP){            // check the end of the heap
				/* handle if there is small available size to allocate*/
						/*here*/
						
				
				
				printf("\nEnd of heap\n");
				//sleep(1);
				return NULL;
			}
			
			else {							// available to increase the program_brk
				program_brk += ((size/PAGE) + 1)*PAGE;
				DeleteBlock(ret);
				InsertBlockAtEnd( (block_t *)Heap, (void *)ret + size + OFFSET , program_brk -  ((void *)ret + size + OFFSET) ); // create new block with the remaining size
				*(int *)ret= size + OFFSET;
				
				return (void *)ret+OFFSET;
			}
		}
	
		/* case top of the heap is allocated block --> increases program_brk and allocate then add the rest in free list */
		else{							
			ret = (block_t *)program_brk;
			program_brk += ( (size/PAGE) + 1)*PAGE;         // increase program brk
			InsertBlockAtEnd( (block_t *)Heap, (void *)ret + size + OFFSET , program_brk -  ((void *)ret + size + OFFSET) ); // create new block with the remaining size
			*(int *)ret= size + OFFSET;
				
			return (void *)ret+OFFSET;
		}
	}
	
}




void HmmFree(void *ptr){
	ptr -= OFFSET;
	int size = *(int *)ptr;
	block_t *block_before;
	block_t *block_after;
	bool merge_3blocks_condition;
	bool merge_2blocks_condition;
	
	/* Search  for the block located before the allocated block */
	block_before = SearchAddress((block_t *)Heap , (block_t *)ptr);
	
	
	if(NULL == block_before){		//no free blocks located before the allocated block 
		
		((block_t *)Heap) -> next_free_block -> previous_free_block = ((block_t *)ptr);
		((block_t *)ptr)  -> previous_free_block = ((block_t *)Heap);
		((block_t *)ptr)  -> next_free_block = ((block_t *)Heap) -> next_free_block;
		((block_t *)Heap) -> next_free_block = (block_t *)ptr;
		
		((block_t *)ptr) -> length = size;
		
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
}

/*===============================================================================================================================================================*/

/*** Adding Node after the Passed Node in the first Argument
     add new_block after block_before
***/

void InsertBlockAfter(block_t *block_before , block_t *new_block , int data){
		block_t *local_block = block_before;
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

void InsertBlockAtEnd(block_t *head , block_t *new_block , int data){
	block_t *local_block = head;
	
	while( NULL != local_block -> next_free_block ){
		local_block = local_block -> next_free_block;
	}
	
	new_block -> next_free_block     = NULL;		// link the next of the inserted block by  NULL
	new_block -> previous_free_block = local_block;		// link the previous of the inserted block by the last block
	local_block -> next_free_block  = new_block;		// link the next of the last block to the inserted block
	
	new_block -> length = data;

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
	
	while( (local_block -> length) <= required ){
		
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
		printf("    Address = %i \t length = %i\n" , local_block , local_block -> length);
		printf("\n");		
		local_block = local_block -> next_free_block;
	}
	printf("-----------------\n");		
}

/*===============================================================================================================================================================*/















