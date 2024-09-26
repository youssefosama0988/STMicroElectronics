#ifndef MAIN_H	
#define MAIN_H

/*-----------------Includes---------------------*/
#define _XOPEN_SOURCE 700
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
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
#include <time.h>
#include <sys/ioctl.h>

/*-----------------Macros---------------------*/
#define PATH_MAX         256

/*-----------------Variables Declaration---------------------*/

extern char *optarg;
extern int optind, opterr, optopt;
extern int errno;

/*-----------------User defined types---------------------*/

typedef struct{
	int file_size;
	int file_name;
	int file_gr;
	int file_owner;
	int file_inode;
	int file_time;
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
	bool d_opt 	    	;
}Options_t;

typedef struct{
	char name[256];
	struct stat Files;

}CombinedStat_t;

/*-----------------Functions Declaration---------------------*/

int GetEntries(char *dirName,CombinedStat_t Entries[]);
MaxSizes_t* GetLstat(char *dir_path , CombinedStat_t Entries[]);
void NormalPrint(MaxSizes_t* max_sizes , CombinedStat_t* Entries, Options_t* options);
void PrintOneLine(MaxSizes_t* max_sizes , CombinedStat_t* Entries , Options_t* options);
void PrintLongFormat(char *dir_path , MaxSizes_t* max_sizes , CombinedStat_t* Entries , Options_t* options);
int cmpstringp(const void *p1, const void *p2);
int Cmp_Atime(const void *p1, const void *p2);
int Cmp_Ctime(const void *p1, const void *p2);
int Cmp_Mtime(const void *p1, const void *p2);

#endif
