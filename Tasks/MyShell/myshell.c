#include "commands.h"


int main(){
	char *token[TOKENS_NO];
	const char *shellmsg = "\033[1;33menter your command :) $\033[0m ";
	ssize_t inputsize =0;
	char input[COMMAND_LENGTH];
	char tty_fd;
	int pipe_index;
	
	printf("pid = %d\n",getpid());
	tty_fd = dup(STDOUT);          // save tty info
	
	
	while(1){
		token_counter = 0;
		
                /* read the command after writing the sell message*/
                memset(input , '\0' , 512);
                write( STDOUT , shellmsg , strlen(shellmsg) );
                inputsize = read(STDIN , input , COMMAND_LENGTH);
                
                if( input[0] == '\n' )         //check if enter is pressed so skip & keep asking for command
                	continue;
                
               
                /* get the tokens of the commandline and save it in array , command = token[0]*/
                token[token_counter] = strtok( input , " \n"); 
                while(token[token_counter] != NULL){
                	token_counter++;
                	token[token_counter] = strtok( NULL , " \n");	
                
                }
                             
                /*---------- check Redirections , return pipe index if exist , 0 on success , -1 on fail  ----------*/
                pipe_index = handleRedirection(token);
                
                /* -------------handle pipe----------*/
                if(pipe_index > 0){
                	int pipeFd[2];
                	int pid1 , pid2;
                	int child_status;
                	
                	
                	/*create the pipe */
                	
                	if( pipe(pipeFd)  == -1){
				perror("Pipe");                	
                	}
                	/* create fork to handle the two proccesses */
                	pid1 = fork();
                	if( -1 == pid1){
				perror("fork1");                	
                	}
                	else if(0 == pid1){   // Child 1 excute first command
                		
                		/* output redirection to the pipeF[1]*/
                		redirection(pipeFd[1] , STDOUT);
                		//close(pipeFd[0]);
                		execute(token);
                		exit(0);
                	
                	}
                	else{	            // Parent
                		pid2 = fork();
                		
                		if( -1 == pid2){
				perror("fork2");                	
		        	}
		        	else if(0 == pid2){   // Child 2 excute second command
		        		
		        		/* read redirection to the pipeF[0]*/
		        		handleRedirection( &token[pipe_index+1] );
		        		redirection(pipeFd[0] , STDIN);
		        		close(pipeFd[1]);
		        		execute(&token[pipe_index + 1]);  //execute the second command which is after | sign
		        		exit(0);
		        	
                		}
                	}
                	
                	/* Close both ends of the pipe in the parent */
                	close(pipeFd[0]); 
			close(pipeFd[1]);

			/** Wait for both children to finish **/
			waitpid(pid1, NULL, 0);
			waitpid(pid2, NULL, 0);
                	
                }
                
                /* Single command*/
                else{
                	execute(token);
                }
                
                
		
		/* restore STDOUT ,STDIN , STRERR*/
		dup2(tty_fd , STDOUT);
                dup2(tty_fd , STDIN);
                dup2(tty_fd , STDERR);
              
	}

	return 0 ;
}



