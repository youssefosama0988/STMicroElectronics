#include <stdio.h>
#include <signal.h>
#include <stdlib.h>



int main(int argc , char** argv){

	union sigval real_time_sig;
	int recv_pid;

	recv_pid = atoi(argv[1]);
	real_time_sig.sival_int = atoi(argv[2]);

	if(sigqueue(recv_pid , SIGRTMIN+5 , real_time_sig ) == 0 ){
	
		printf("Signal Sent Successfully!\n");

	}
	else{
		perror("SigQueue ");
	}

	return 0;
}
