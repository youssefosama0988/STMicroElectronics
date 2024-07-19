//#include <stdio.h>
//#include <elf.h>
#include "secondFile.h"

int globalinit=5,global;
static int staticVar = 10;

int main(){
	int local=2;
	
	printf("Function calling.... \n");
	printSum();
	printf("Working!!\n");
	printf("%d %d %d %d \n", globalinit ,global ,staticVar ,local );
	
	return 0 ;	    
}


