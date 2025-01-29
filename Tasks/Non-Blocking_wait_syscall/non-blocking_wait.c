

#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/**********************************Functions Declarations*****************************************/
void SIGCHILD_handler(int signo, siginfo_t *info, void *ucontext);
int non_blocking_wait(int *status);
void undo_waiting(void);

/*========Main=============*/
int main(){

	int pid;
	
	pid = fork();
	
	if(pid == 0){			//child
		printf("CHILD : waiting for termination \n");
		getchar();
		exit(5);
	}
	else if(pid > 0){              //parent
	
		non_blocking_wait(NULL);
		printf("Parent : waiting for childrens\n");
		while(1);
		//undo_waiting();			/*to undo waiting for childrens, make SIGCHLD handler is default*/
		//while(1);
	}
	else{
	
		perror("fork ");
	}

	return 0;
}

void SIGCHILD_handler(int signo, siginfo_t *info, void *ucontext){

	if(signo != SIGCHLD){
		printf("wait: Recieved another signal\n");
		return;
	}
	
	if(info->si_code == CLD_EXITED){
		printf("Child pid -> %i | Child Exit normally with value %i\n",info->si_pid , info->si_status);
	}
	else if(info->si_code == CLD_KILLED){
		printf("Child pid -> %i | Child KILLED by %s signal \n",info->si_pid , strsignal(info->si_status) );
	}
	else{
		printf("Child exit abnormally\n");
	}	
	
	return;
	
}

int non_blocking_wait(int *status){

	struct sigaction sa;
	int sa_ret;
	
	sa.sa_sigaction = SIGCHILD_handler;
	sa.sa_flags = SA_SIGINFO | SA_NOCLDWAIT;    
	
	sa_ret = sigaction(SIGCHLD , &sa , NULL);
	
	if(-1 == sa_ret){
		perror("sigaction ");	
	}
		
}


void undo_waiting(void){

	struct sigaction sa;
	int sa_ret;
	
	sa.sa_handler = SIG_DFL; 
	
	sa_ret = sigaction(SIGCHLD , &sa , NULL);
	
	if(-1 == sa_ret){
		perror("sigaction ");	
	}

}







