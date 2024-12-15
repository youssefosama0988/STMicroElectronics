#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void RealTimeHandler(int sig , siginfo_t* info , void* ucontext){

	int recieved_value;

	recieved_value = info->si_value.sival_int;

	if(0 == recieved_value){
		printf("Oops this process will be terminated \n");
		printf("Recieved Value = %i\n" , recieved_value);
		exit(0);
	
	}
	else if(1 == recieved_value){
		printf("this process will be terminated and generates a core dump file \n");
		printf("Recieved Value = %i \n" , recieved_value);
		abort();
	}
	else{
		printf("the process recieved value not handled and it will be continued\n");
		printf("Recieved Value = %i \n" , recieved_value);
	}
}


int main(){


	struct sigaction RT_sigaction;

	RT_sigaction.sa_sigaction = RealTimeHandler;
	RT_sigaction.sa_flags = SA_RESTART | SA_SIGINFO;

	if(sigaction( SIGRTMIN+5 , &RT_sigaction , NULL) < 0 )
		perror("SigAction ");
	

	while(1){
		printf("Reciever Ready for incoming Real Time Signal \n ");
		pause();
	}

	return 0;

}
