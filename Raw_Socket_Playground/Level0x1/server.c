/*
    A Multi-Client Server
    Concurrency Method: One Client Per Process (Each connected client gets a
   separate process)
*/

#include "utils.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define MAX_CLIENTS 10

// Function Prototype.
void handle_client(int client_sock);

int main(int argc, char *argv[])
{
    // check for proper arguments.
    if (argc != 3)
    {
        printf("usage: %s <option>\noptions:\t-p <port>"
               "\n[Exiting...]\n",
               argv[0]);
        return EXIT_FAILURE;
    }
    else if (strcmp(argv[1], "-p") != 0)
    {
        printf("usage: %s <option>\noptions:\t-p <port>"
               "\n[Exiting...]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    int port = get_port(argv[2]);
    if (port == -1)
    {
        fprintf(stderr, "[x] Invalid Port: %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // Create the server socket.
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[x] Socket Creation! [FAILED]");
        exit(EXIT_FAILURE);
    }
    printf("[+] Server Socket Created!: FD %d [SUCCESS]\n", server_sock);

    // Define the server address structure.
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    socklen_t server_addr_len = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address.
    if (bind(server_sock, (struct sockaddr *)&server_addr, server_addr_len) < 0)
    {
        perror("[x] Binding! [FAILED]");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming client connection.
    if (listen(server_sock, 1) < 0)
    {
        perror("[x] Listening! [FAILED]");
        exit(EXIT_FAILURE);
    }
    printf("[+] Listening On Port: %d [SUCCESS]\n", atoi(argv[2]));

    // Accept incoming client connection.
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sock;

    while (0x1)
    {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr,
                             &client_addr_len);
        if (client_sock < 0)
        {
            if (errno == EINTR)
            {
                continue; // Retry accept()...
            }
            else
            {
                perror("[x] Accept! [FAILED]");
                exit(EXIT_FAILURE);
            }
        }
        printf("[+] New Client Online: FD %d [SUCCESS]\n", client_sock);

        // Spawn a new process for the new client.
        pid_t pid = fork();
        if (pid == 0) // Child Process.
        {
            // Close the listening socket.
            close(server_sock);

            // Handle the new client.
            handle_client(client_sock);
            close(client_sock);
            exit(EXIT_SUCCESS);
        }
        else if (pid > 0) // Parent Process.
        {
            close(client_sock);

            // Reap the finished children.
            pid_t dead_pid, status;

            while ((dead_pid = waitpid(-1, &status, WNOHANG)) > 0)
            {
                // Clean up finished child.
                printf("[Zzz] Child Process %d: Status %d [REAPED!]\n",
                       dead_pid, status);
            }
        }
        else
        {
            // Handle fork error.
            perror("[x] Process Fork! [FAILED]");
            exit(EXIT_FAILURE);
        }
    }

    close(server_sock);

    return EXIT_SUCCESS;
}

void handle_client(int client_sock)
{
    // Handle connected clients.
    // Send message to client.
    const char *message = "Welcome To The Dojo! Warrior";

    ssize_t bytes_sent = send(client_sock, message, strlen(message), 0);
    if (bytes_sent < 0)
    {
        perror("[x] Sending! [FAILED]");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    ssize_t bytes_received;

    // Receive client message and echo it back.
    while ((bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) >
           0)
    {
        if (bytes_received == 0)
        {
            perror("[-] Client! [DISCONNECTED]");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_received] = '\0';
        printf("[+] Received %zu bytes from client [%s]\n", bytes_received,
               buffer);

        // Echo back the message to the client.
        ssize_t bytes_sent = send(client_sock, buffer, bytes_received, 0);
        if (bytes_sent < 0)
        {
            perror("[x] Sending! [FAILED]");
            exit(EXIT_FAILURE);
        }
        printf("[+] Sent %zu bytes to client [SUCCESS]\n", bytes_sent);
    }
}
