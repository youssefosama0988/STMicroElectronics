#include "commands.h"



char *token[6];
int token_counter=0;


/*===================================================================================================================================================================*/

void myexit(void){
	write(STDOUT , " Goodbye! :) \n" , strlen(" Goodbye! :) \n") );
}

/*===================================================================================================================================================================*/

int pwd(void){

	char cwd[PATH_LENGTH];
	if( getcwd( cwd , PATH_LENGTH ) != NULL){
		printf("Current Working Directory : %s \n" , cwd);
		return 0 ;
	}	
	else{
	       	perror("Failed! ");
		return -1;
	}	
}

/*===================================================================================================================================================================*/

int  echo(void){
	token_counter = 1;
	
	if(NULL == token)
		return -1;
	else{
		
		while(token[token_counter] != NULL){
			printf("%s ",token[token_counter]);
			token_counter++;
		}
		printf("\n");
		return 0;
	}
}

/*===================================================================================================================================================================*/

void myhelp(void){
	write(STDOUT , " Supported Commands \n" , strlen(" Supported Commands \n"));
	write(STDOUT , "   1) pwd: print working directory \n" , strlen(" 1) pwd: print working directory \n"));
	write(STDOUT , "   2) echo: print a user input string on stdout \n" , strlen("   2) echo: print a user input string on stdout \n"));
	write(STDOUT , "   3) mycp: copy a file to another file (cp sourcePath targetPath)\n" , strlen("   3) mycp: copy a file to another file (cp sourcePath targetPath)\n"));
	write(STDOUT , "   4) mymv: move a file to another place (mv sourcePath targetPath)\n" , strlen("   4) mymv: move a file to another place (mv sourcePath targetPath)\n"));
	write(STDOUT , "   5) myexit: print 'Goodbye!' and terminate the shell\n" , strlen("   5) myexit: print 'Goodbye!' and terminate the shell\n"));
	write(STDOUT , "   6) myhelp: print all the supported commands \n" , strlen("   6) myhelp: print all the supported commands \n"));				

}

/*===================================================================================================================================================================*/

char targetPath[100] , sourcePath[100];   /* GLOBAL to use in MOVE function*/
int mycp(void){
	
	int fd_source , fd_target;
	char buffer[200];
	int size = 0;
	char *fileName_target , *fileName_source;
	char *temp;
	
	strcpy( targetPath , token[2]);
	strcpy( sourcePath , token[1]);
	
		
	/* get the source file name */
	temp = strtok(token[1] , "/");
	while( temp != NULL){
		fileName_source = temp;
		temp = strtok(NULL , "/"); 
	}
	
	
	/* check if the user enter file name or just the directory -------'case'-------> Dir. so create new file with same name of the source file */
	if( token[2][strlen( token[2] ) - 1] == '/'){
		fileName_target = fileName_source;
		strcat(targetPath , fileName_target );
	}

	/*------------------------------ Start Opening the files -------------------------------------*/
	
	fd_source = open( sourcePath , O_RDONLY);
	
	if(fd_source == -1){
		perror("Failed to open Source ");
		return -1;
	}
	
	/* when the source file opened successfully*/
	else {
		
		/* Check if there is an option or not. ex: -a option */
		
		if(token[3] != NULL){
			if(strcmp(token[3],"-a") == 0)          /* token[3] = option "-a" append the file */
				fd_target = open(targetPath , O_CREAT | O_WRONLY | O_APPEND , S_IRWXU);
			else if(strcmp(token[3],"-f") == 0)      /* token[3] = option "-f" over write the file */
				fd_target = open(targetPath , O_CREAT | O_WRONLY | O_TRUNC| O_APPEND , S_IRWXU);	
			else{ 
				printf("%s : not supported option\n" , token[3]);
				//fd_target = -1;
			}
				
		}		
		else{ 	
			fd_target = open(targetPath , O_CREAT | O_WRONLY | O_TRUNC | O_EXCL , S_IRWXU);
		}
		
		if(fd_target == -1){
			perror("Failed! ");
			return -1;
		}
		
		/* Start Copying if all is done and the file created or opened*/
		do{
		size = read(fd_source  , buffer , 200);
		write(fd_target , buffer , size);	
		
			if( size == -1){
				perror("Operation is Failed! ");
				return -1;
			}
		}while(size);
			
	}
		
	close(fd_source);
	close(fd_target);
	
	return 0 ;
	
}

/*===================================================================================================================================================================*/

int mymove(void){
	int done = 0;
	/* Call cp Function to copy the content of the file to target*/
	done = mycp();
	
	if(-1 == done){
		write(STDOUT , " Failed to copy \n" , strlen(" Failed to copy \n") );
		return  -1;
	}
	
	/* Remove the Source File */
	done = unlink(sourcePath);
	if( -1 == done){
		perror("Deleting Failed ");
		return -1 ;
	}
	return 0 ;
}

/*======================================================================================================================================================================*/

int mycd(void){

	char cwd_prev[PATH_LENGTH];
	char cwd_new[PATH_LENGTH];
	char temp[PATH_LENGTH];
	int counter;
	
	if( NULL != token[1] ){
		
		
		strcpy( temp , token[1] );
		getcwd(cwd_prev , PATH_LENGTH);
			
		/* if the user enter '..' or '../' go to the parent dir.*/
		if( strcmp(token[1] , "..") == 0 || strcmp(token[1] , "../") == 0 ){
			counter = strlen(cwd_prev) - 1 ;
			while( cwd_prev[counter] != '/' ){
				counter--;
			}
			cwd_prev[counter] = '\0';
			strcpy(cwd_new , cwd_prev);     
		}
		
		/* if the user enter '/' go to this absolute dir. if exist*/
		else if( token[1][0] == '/' ){
			strcpy(cwd_new ,token[1]);	
		}
		
		/* if the user enter './fileName' or '../fileName' */
		else{
			/* check if the user enter '..' in the first token */
			if(strcmp( strtok(temp , "/\n") ,".." ) == 0){
				counter = strlen(cwd_prev) - 1 ;
				while( cwd_prev[counter] != '/' ){
					counter--;
				}
				cwd_prev[counter] = '\0';
				strcpy(cwd_new , strcat( cwd_prev , &(token[1][2]) ) );    //token[1][2] = points to the slash in "../fileName" 			
			}
			
			else{ 
				strcat( cwd_prev, "/");
				strcpy(cwd_new , strcat( cwd_prev, token[1] ) );
			}
		}
		
		/* use system call chdir to change the current directory with cwd_new */
		if( chdir(cwd_new) == -1){
			printf("%s \n" , cwd_new );
			perror("cd Failed ");
			return -1;
		}
	}
	else{
		printf("No Arg. \n");
		return -1;
	}		
		
	return 0;
}

/*======================================================================================================================================================================*/

void envir(void){
	int counter = 0;
	while(environ[counter] != NULL){
		printf("%s \n" , environ[counter]);
		counter++;
	}
}

/*======================================================================================================================================================================*/

int type(void){
	char *InternalCommands[]={"echo" , "pwd" , "mycp" , "mymv" , "myexit" , "myhelp" , "cd" , "envir" , "type" };
	int counter;
	char fullPath[PATH_LENGTH];
	char *path;          
	char temp[PATH_LENGTH];
	char *directory;
	
	if(NULL == token[1]){
		printf("No Arg.\n");
		return -1;
	}
	/* Case of Internal Commands */
	for(counter = 0 ; counter < BUILTINCOMMANDS ; counter++){
		if( strcmp(token[1] , InternalCommands[counter]) == 0 ){
			printf("%s is a Built In Command \n",token[1]);
			return 0;
		}
	}
	
	/* Search for External Commands*/
	path = strdup( getenv("PATH") );
	if(NULL == path)
		return -1;
	
	directory = strtok(path ,":");
	while(NULL != directory){
		strcpy(temp , directory);
		strcat(temp,"/");
		strcpy( fullPath , strcat(temp,token[1]) );
		if(access(fullPath , X_OK) == 0){
			printf("%s is External Command\n",token[1]);
			return 0;
		}
		directory = strtok(NULL,":");		
	}
	
	printf("%s is Unsupported Command\n",token[1]);					
	return 0;
}

/*======================================================================================================================================================================*/

int externalCommands(void){
	int pid;
	int exec_ret;
	int child_status;

	pid = fork();
	
	if(pid > 0){
		pid = wait(&child_status);
		/* handle exit status of the Child */
	}
	
	/* the child going to execute the command and terminates, if fails to find the program, exit with -1 */
	else if(pid == 0){

		printf("%s\n" , token[0] );
		exec_ret = execvp(token[0] , token);
		if(exec_ret == -1){
			perror("Unsupported Command ");
			exit(-1);
		}	
	}
	
	else {
		perror("Fork Failed ");
		return -1;
	}
	return 0;

}

/*======================================================================================================================================================================*/





