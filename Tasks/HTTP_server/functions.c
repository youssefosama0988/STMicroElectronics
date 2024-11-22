
#include "functions.h"

/*====================================================================================================================================*/

// Function to send a basic HTTP response
void send_response(int client_fd, const char *status, const char *content_type, const char *body) {
    char response[BUFFER_SIZE];
    sprintf(response, "HTTP/1.1 %s\r\nContent-Type: %s\r\nContent-Length: %lu\r\n\r\n%s",
            status, content_type, strlen(body), body);
    send(client_fd, response, strlen(response), 0);
}

/*====================================================================================================================================*/


// Function to list directory contents
void handle_directory_request(int client_fd, const char *path) {
	DIR *dir; 
	struct dirent *entry;
	char body[BUFFER_SIZE] = "<html><body><ul>";

	dir = opendir(path);
	if (NULL == dir) {
		send_response(client_fd, "500 Internal Server Error", "text/plain", "Unable to open directory.\n");
		return;
	}


	while ((entry = readdir(dir)) != NULL) {
		strcat(body, "<li>");
		strcat(body, entry->d_name);
		strcat(body, "</li>");
	}
	strcat(body, "</ul></body></html>");

	closedir(dir);
	send_response(client_fd, "200 OK", "text/html", body);
}

/*====================================================================================================================================*/


// Function to serve regular files
void handle_regular_file_request(int client_fd, const char *path){
	int fd;
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read;
	char body[BUFFER_SIZE] = "";
	
	fd = open(path, O_RDONLY);
	
	if (-1 == fd) {
		send_response(client_fd, "404 Not Found", "text/plain", "File not found.\n");
		return;
	}

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE - 1)) > 0) {
		buffer[bytes_read] = '\0';
		strcat(body, buffer);
	}
	close(fd);

	send_response(client_fd, "200 OK", "text/plain", body);
}

/*====================================================================================================================================*/


void handle_cgi_request(int client_fd, const char *path) {
    int pipe_fd[2]; // Pipe for communication between parent and child
    
    if (pipe(pipe_fd) == -1) {
        send_response(client_fd, "500 Internal Server Error", "text/plain", "Failed to create pipe.");
        return;
    }

    pid_t pid = fork();
    if (pid < 0) {
        send_response(client_fd, "500 Internal Server Error", "text/plain", "Failed to fork process.");
        return;
    }

    if (pid == 0) { 		//Child process
        
        close(pipe_fd[0]); 		//Close read end of pipe
        dup2(pipe_fd[1], STDOUT); 	//Redirect stdout to pipe
        close(pipe_fd[1]); 		//Close write end of pipe (after duplication)

        //Execute the CGI script
        execl(path, path, NULL);

        perror("execl");
        exit(1);
        
    }
    else{ 			//Parent process
        
        close(pipe_fd[1]); 	//Close write end of pipe
	
	int status;
        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        char body[BUFFER_SIZE] = "";

        // Read the output from the child process
        while ((bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0';
            strcat(body, buffer);
        }
        close(pipe_fd[0]); // Close read end of pipe

        // Wait for the child process to complete
        waitpid(pid, &status, 0);

        // Send the CGI script's output as the response
        send_response(client_fd, "200 OK", "text/plain", body);
    }
}


/*====================================================================================================================================*/


// Main handler for HTTP requests
void handle_request(int client_fd){
    char buffer[BUFFER_SIZE];
    char method[16];
    char path[256];
    struct stat path_stat;
    
    recv(client_fd, buffer, BUFFER_SIZE, 0);

    /************************************************************
    ******************* Parse HTTP request **********************
    ************************************************************/
    
    sscanf(buffer, "%s %s", method, path);    //get the path and the method

    // Remove leading '/' from path
    char resolved_path[256] = ".";
    strcat(resolved_path, path);

    // Check if file or directory exists
    
    if (stat(resolved_path, &path_stat) == -1) {
        send_response(client_fd, "404 Not Found", "text/plain", "Resource not found. Try another one :)\n");
        return;
    }

    // Handle based on file type
    if (S_ISDIR(path_stat.st_mode)) {
        handle_directory_request(client_fd, resolved_path);
    }
    else if (S_ISREG(path_stat.st_mode)) {
        if (strstr(resolved_path, ".cgi")) {
		handle_cgi_request(client_fd, resolved_path);
	}
        else{
            handle_regular_file_request(client_fd, resolved_path);
        }
    } 
    else{
        send_response(client_fd, "400 Bad Request", "text/plain", "Unsupported resource type :(\n");
    }
}


/*====================================================================================================================================*/



