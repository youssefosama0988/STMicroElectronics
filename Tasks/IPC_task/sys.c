
#include "system.h"

void read_lock(int fd)
{

	struct flock lock;

	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;		//lock the whole file

	/***********************lock the file***************************/
	lock.l_type = F_RDLCK;	// take read lock

	if (fcntl(fd, F_SETLK, &lock) == -1) {
		perror("Error take read lock");
		exit(-1);
	}

}

void write_lock(int fd)
{

	struct flock lock;

	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;		//lock the whole file

	/***********************lock the file***************************/
	lock.l_type = F_WRLCK;	// take write lock

	if (fcntl(fd, F_SETLK, &lock) == -1) {
		perror("Error take write lock");
		exit(-1);
	}

}

void unlock(int fd)
{

	struct flock lock;

	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;		//lock the whole file

	/***********************unlock the file***************************/
	lock.l_type = F_UNLCK;	// take read lock

	if (fcntl(fd, F_SETLK, &lock) == -1) {
		perror("Error releasing lock");
		exit(-1);
	}

}
