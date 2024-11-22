
/***************************************Includes*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>

/*************************************** Macros *******************************************/
#define BUFFER_SIZE (4096*2)
#define STDOUT       0


/**************************** Functions Declarations ***************************************/

void send_response(int client_fd, const char *status, const char *content_type, const char *body);
void handle_directory_request(int client_fd, const char *path);
void handle_regular_file_request(int client_fd, const char *path);
void handle_cgi_request(int client_fd, const char *path);
void handle_request(int client_fd);
