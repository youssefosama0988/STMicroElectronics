#include "functions.h"


int main(int argc ,char **argv) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Bind socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[1]));
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("HTTP server running on port %s\n", argv[1]);
    printf("********************* The Server is Ready ********************\n\n");

    // Accept and handle clients
    while ((client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len)) >= 0) {
        handle_request(client_fd);
        close(client_fd);
    }

    close(server_fd);
    return 0;
}

