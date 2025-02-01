#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define ERROR     1
#define WARNING   2
#define INFO      3
#define DEBUG	  4
#define DISABLE   0


int main(int argc , char** argv){

	union sigval real_time_sig;
	int recv_pid;

	recv_pid = atoi(argv[1]);
	
	if(strcmp(argv[2] , "error") == 0)
		real_time_sig.sival_int = ERROR;
	else if(strcmp(argv[2] , "warning") == 0)
		real_time_sig.sival_int = WARNING;
	else if(strcmp(argv[2] , "info") == 0)
		real_time_sig.sival_int = INFO;
	else if(strcmp(argv[2] , "debug") == 0)
		real_time_sig.sival_int = DEBUG;			
	else if(strcmp(argv[2] , "disable") == 0)
		real_time_sig.sival_int = DISABLE;			
	else{ 
		printf("Unsupported level\n");
		return -1;
	}
	if(sigqueue(recv_pid , SIGRTMIN+5 , real_time_sig ) == 0 ){
	
		//printf("Signal Sent Successfully!\n");

	}
	else{
		perror("SigQueue ");
	}

	return 0;
}
