#include "commands.h"

int token_counter=0;


/*===================================================================================================================================================================*/

void myexit(void){
	write(STDOUT , " Goodbye! :) \n" , strlen(" Goodbye! :) \n") );
	exit(0);
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

int  echo(char *token[]){
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
	write(STDOUT , "   7) cd path : change the current directory \n" , strlen("   6) cd path : change the current directory \n"));				
	write(STDOUT , "   8) type command : return the type of the command 'internal, external or unsupported command' \n" , strlen("   8) type command : return the type of the command 'internal, external or unsupported command' \n"));				
	write(STDOUT , "   9) envir command without any args : print all the environment variables  \n" , strlen("   9) envir command without any args : print all the environment variables  \n"));						
}

/*===================================================================================================================================================================*/

char targetPath[100] , sourcePath[100];   /* GLOBAL to use in MOVE function*/
int mycp(char *token[]){
	
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

int mymove(char *token[]){
	int done = 0;
	/* Call cp Function to copy the content of the file to target*/
	done = mycp(token);
	
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

int mycd(char *token[]){

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

void envir(char *token[]){
	int counter = 0;
	char *variable;
	//char variable[64];
	/* if there is no Argument */
	if(NULL == token[1]){
		while(environ[counter] != NULL){
			printf("%s \n" , environ[counter]);
			counter++;
		}
	}
	/* if there is an argument so it print the value of the environment variable */
	else{	
		if( NULL != getenv(token[1])){                    //exist
			variable = strdup( getenv(token[1]) );
			
			if(NULL == variable)
				printf("malloc failed\n");
			else{	
			printf("%s\n",variable);
			}
			free(variable);		
		}
		
		else
			printf("%s Not Found\n",token[1]);	
	}

}

/*======================================================================================================================================================================*/

int type(char *token[]){
	char *InternalCommands[]={"echo" , "pwd" , "mycp" , "mymv" , "myexit" , "myhelp" , "cd" , "envir" , "type" , "myfree" , "myuptime"};
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
			free(path);
			return 0;
		}
		directory = strtok(NULL,":");		
	}
	
	printf("%s is Unsupported Command\n",token[1]);		
	free(path);			
	return 0;
}

/*======================================================================================================================================================================*/

int myfree(void){

	char buff[PATH_LENGTH];
    	FILE *meminfo;
    	unsigned long mem_total = 0, mem_free = 0, cached = 0, buffers = 0 ;
    	unsigned long swap_total = 0 , swap_free = 0;

    	meminfo = fopen(MEMINFO_PATH , "r");
    	if (meminfo == NULL) {
		perror("open meminfo ");
		return -1;
    	}

    	/*read each line and get the values*/
	while (fgets(buff, LINE, meminfo)) {

		if (strncmp(buff, "MemTotal:", 9) == 0){
			mem_total = strtol(buff + 9, NULL, 10);
		}
		else if (strncmp(buff, "MemFree:", 8) == 0){
			mem_free = strtol(buff + 8, NULL, 10);
		}
		else if (strncmp(buff, "Cached:", 7) == 0){
			cached = strtol(buff + 7, NULL, 10);
		}
		else if (strncmp(buff, "Buffers:", 8) == 0){
			buffers = strtol(buff + 8, NULL, 10);
		}
		else if (strncmp(buff, "SwapTotal:", 10) == 0){
			swap_total = strtol(buff + 10, NULL, 10);
		}
		else if (strncmp(buff, "SwapFree:", 9) == 0){
			swap_free = strtol(buff + 9, NULL, 10);
		}

	}


	fclose(meminfo);

	printf("MemTotal:     \t %ld kB\n", mem_total);
	printf("MemFree:      \t %ld kB\n", mem_free);
	printf("Cache/buff:   \t %ld kB\n", cached + buffers);
	printf("MemUsed:      \t %ld kB\n", (mem_total - mem_free - cached -buffers) );
	printf("-----------------------------\n");
	printf("SwapTotal:    \t %ld kB\n", swap_total);
	printf("SwapFree:     \t %ld kB\n", swap_free);
	printf("SwapUsed:     \t %ld kB\n", (swap_total - swap_free) );
	

	return 0;
}

/*======================================================================================================================================================================*/

int myUpTime(void){
	int fd;
	int read_size = 0;
	char buff[LINE];
	char *tok;
	
	fd = open(UPTIME_PATH , O_RDONLY);
	if(-1 == fd){
		perror("open ");
		return -1;
	}
	
	read_size = read(fd,buff,LINE);
	if(read_size > 0){
		tok = strtok(buff," ");
		printf("uptime for the system(s):           %s s\n",tok);
		tok = strtok(NULL,"\n ");
		printf("time spent in the idle process(s):  %s s\n",tok );	
		return 0;
	}
	else if( 0 == read_size){
		printf("EOF!\n");
		return -1;
	}
	else if( -1 == read_size){
		perror("read ");
		return -1;
	} 
}

/*======================================================================================================================================================================*/

int redirection(int oldFd , int newFd){

	int currFd;
	
	currFd = dup2( oldFd , newFd);
	close(oldFd);

	return currFd;
}

/*======================================================================================================================================================================*/

int handleRedirection(char *token[]){
	int i=0;
	int fd;
	
	
	while(token[i] != NULL){
		
		/* check input redirection */
		if(strcmp(token[i] ,"<") == 0){
			fd = open(token[i+1] , O_RDONLY);
			if(fd == -1){
				perror("open failed");
				return -1;
			}
			redirection(fd , STDIN);
			token[i] =NULL;		
		}
	
		/* check output redirection */		
		else if(strcmp(token[i] ,">") == 0){
			fd = open(token[i+1] , O_CREAT | O_WRONLY | O_TRUNC , S_IRWXU);
			if(fd == -1){
				perror("open failed");
				return -1;
			}
			redirection(fd , STDOUT);	
			token[i] =NULL;	
		} 	
		
		/* check error redirection */		
		else if(strcmp(token[i] ,"2>") == 0){
			fd = open(token[i+1] , O_CREAT | O_WRONLY | O_TRUNC , S_IRWXU);
			if(fd == -1){
				perror("open failed");
				return -1;
			}
			redirection(fd , STDERR);
			token[i] =NULL;		
		}
		
		else if(strcmp(token[i] ,"|") == 0){	
			token[i] =NULL;
			return i;
		}		
		
		i++;
	}
	return 0;	
}

/*======================================================================================================================================================================*/

int externalCommands(char *token[]){
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


int execute(char *token[]){
		int status;
		/****-----------------check which command is entered by the user---------------****/
        
                /* check if the user enter the exit command, the program will terminates */
                if ( !strcmp(token[0] , "myexit")){
                        myexit();
                        exit(0);                
                }
		
		/* check if the user enter the pwd command, the program will print on the terminal the current working directory */
                else if( !strcmp(token[0] , "pwd")){
			status = pwd();
                }
		
		/* check if the user enter the echo command, the program will print the user input command */
		else if(!strcmp(token[0] , "echo")){
			status = echo(token);	
		}
		
		/* check if the user enter the help command, the program will display the supported commands */
		else if(!strcmp(token[0] , "myhelp")){
			myhelp();	
		}
		
		/* check if the user enter the copy command, call cp function */
		else if(!strcmp(token[0] , "mycp")){
			status = mycp(token);	
		}
		
		/* check if the user enter the mv command, call move function */
		else if(!strcmp(token[0] , "mymv")){
			status = mymove(token);	 
		}
		
		/* check if the user enter the cd command, call mycd function */
		else if(!strcmp(token[0] , "cd")){
			status = mycd(token);	
		}
		
		/* check if the user enter the envir command */
		else if(!strcmp(token[0] , "envir")){
			envir(token);	
		}
		
		/* check if the user enter the type command */
		else if(!strcmp(token[0] , "type")){
			type(token);	
		}
		
		/* check if the user enter the free command, call free function */
		else if(!strcmp(token[0] , "myfree")){
			status = myfree();	
		}
		
		/* check if the user enter the free command, call free function */
		else if(!strcmp(token[0] , "myuptime")){
			status = myUpTime();	
		}
		
		/* in case of Unsupported Command */
		else{	
			externalCommands(token);
			
		}
		return status;

}




