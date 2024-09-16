#ifndef MAIN_H	
#define MAIN_H

#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>        
#include <sys/stat.h>
#include <errno.h>
#include <grp.h>
#include <pwd.h>

extern char *optarg;
extern int optind, opterr, optopt;
extern int errno;

typedef struct{
	int file_size;
	int file_name;
	int file_gr;
	int file_owner;
	int file_inode;
}MaxSizes_t;

typedef struct{
	bool all_opt 		;
	bool long_format_opt 	;
	bool c_opt 		;
	bool t_opt 		;
	bool u_opt 	     	;
	bool inode_opt    	;
	bool f_opt 	    	;
	bool oneLine_opt	;
}Options_t;

int GetEntries(char *dirName,struct dirent Entries[]);
MaxSizes_t* GetLstat(char *dir_path , struct dirent Entries[] , struct stat Files[]);
void PrintOneLine(MaxSizes_t* max_sizes , struct dirent Entries[] , Options_t* options);


#endif
