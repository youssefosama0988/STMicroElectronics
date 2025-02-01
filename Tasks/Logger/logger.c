#include "logger.h"

bool 	error 	= false , 
	warning = false , 
	info	= false ,
	debug	= false ;



/***********************************************START OF MAIN************************************************/
int main(){

	struct sigaction RT_sigaction;   //to real-time signals
	sigset_t RT_set;
	
	if( sigfillset(&RT_set) != 0)
		perror("SigFillSet ");
		
	RT_sigaction.sa_sigaction = handler;
	RT_sigaction.sa_flags = SA_RESTART | SA_SIGINFO;
	RT_sigaction.sa_mask = RT_set;
	
	if(sigaction( SIGRTMIN+5 , &RT_sigaction , NULL) < 0 )
		perror("SigAction ");
	
	
	printf("Process ID %i\n" , getpid());
	
	while(1){
		LOG_ERROR("Error Message , take care");
		sleep(1);
		LOG_WARNING("Warning!");
		sleep(1);
		LOG_INFO("Info message :)");
		//sleep(1);
		LOG_DEBUG("Debugging ");	
		//sleep(1);
	}
	 

	return 0;
}


/***********************************************END OF MAIN************************************************/


/* Handler of the real-time signal which set the level of logger*/
void handler(int sig, siginfo_t *siginfo, void *ucontext){
	
	int recieved_value;

	recieved_value = siginfo->si_value.sival_int;

	if(DISABLE == recieved_value){
		error 	= false ; 
		warning = false ; 
		info	= false ;
		debug	= false ;
		printf("DISABLED!\n");
	
	}
	else if(ERROR == recieved_value){
		error = true;
		
		warning = false ; 
		info	= false ;
		debug	= false ;
		printf("Error mode is ON\n"); 
	}
	else if(WARNING == recieved_value){
		warning = true; 
		
		error   = false ; 
		info	= false ;
		debug	= false ;
		printf("Warning mode is ON\n");
	}
	else if(INFO == recieved_value){
		info = true; 
		
		error   = false ; 
		warning	= false ;
		debug	= false ;
		printf("Info mode is ON\n");
	}
	else if(DEBUG == recieved_value){
		debug = true;
		 
		warning = false ; 
		info	= false ;
		error	= false ;
		printf("Debug mode is ON\n");
	}
	else{
		printf("Unhandled Case with Recieved Value = %i \n" , recieved_value);
	}
}

/****************************************************************************************************************/
void Logger_output(int mode , const char *message ){

	if(mode == ERROR && error){
		printf("\033[31m%s\033[0m\n" , message);		//red
	}
	else if(mode == WARNING && warning){
		printf("\033[45m%s\033[0m\n" , message);		//purple
	}
	else if(mode == INFO && info){
		printf("%s\n" , message);
	}
	else if(mode == DEBUG && debug){
		printf("\033[44m%s\033[0m\n" , message);		//blue
	}
	else{
	
		//printf("unhandled mode\n");	
	}

}






