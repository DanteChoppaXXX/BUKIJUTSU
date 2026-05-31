// This program accept connection from clients, receive their message and echoes it back to the client.

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ucontext.h>
#include <unistd.h>

#define PORT 9999
#define IP "127.0.0.1"
#define BUFFER_SIZE 1024

// Client argument struct.
typedef struct{
    int client_socket;
} ClientArgs;

// Function prototype.
void clientHandler(void *arg);

int main(void)
{
    // Create the server socket.
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) 
    {
        fprintf(stderr, "[x] SOCKET CREATION [FAILED]\n");
        return EXIT_FAILURE;
    }
    printf("[+] SOCKET CREATED ON FD %d [SUCCESS]\n", server_socket);

    // Define the address structure.
    struct sockaddr_in server_address;
    socklen_t server_address_len = sizeof(server_address);

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = inet_addr(IP);

    // Bind the socket to the address.
    if (bind(server_socket, (const struct sockaddr *)&server_address, server_address_len) < 0)
    {
        fprintf(stderr, "[x] BINDING [FAILED]\n");
        close(server_socket);
        return EXIT_FAILURE;
    }
    printf("[+] SOCKET BOUND TO ADDRESS %s [SUCCESS]\n", IP);

    // Listen for incoming connections.
    if (listen(server_socket, 3) < 0) 
    {
        fprintf(stderr, "[x] LISTENING [FAILED]\n");
        close(server_socket);
        return EXIT_FAILURE;
    }
    printf("[+] SERVER IS LISTENING ON PORT %d [SUCCESS]\n", PORT);

    // Define the client address structure
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);

    // Accept incoming client connections.
    while (1)
    {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket < 0) 
        {
            fprintf(stderr, "[x] ACCEPT [FAILED]\n");
            close(server_socket);
            return EXIT_FAILURE;
        }
        printf("[+] NEW CLIENT ACCEPTED ON FD %d [SUCCESS]\n", client_socket);

        ClientArgs *client_args = malloc(sizeof(ClientArgs));
        if (client_args == NULL)
        {
            fprintf(stderr, "[x] Memory Allocation! [FAILED]\n");
            close(server_socket);
            exit(EXIT_FAILURE);
        }

        client_args->client_socket = client_socket;

        clientHandler(&client_args->client_socket);
    }

}

void clientHandler(void *arg)
{
    ClientArgs *client_socket = (ClientArgs *) arg;

    // Send welcome message to the client.
    const char *message = "WELCOME TO THE SERVER\n";
    // int len = strlen(message);
    ssize_t bytes_sent = send(client_socket->client_socket, message, strlen(message), 0);
    if (bytes_sent < 0)
    {
        fprintf(stderr, "[x] SENDING [FAILED]\n");
        close(client_socket->client_socket);
        free(client_socket);
    }
    printf("[+] WELCOME MESSAGE SENT [SUCCESS]\n");

    // Receive client message and echo it back to client.
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;
    while ((bytes_received = recv(client_socket->client_socket, buffer, BUFFER_SIZE, 0)) > 0)
    {
        // Receive message from client.
        if (bytes_received == 0) 
        {
            printf("[!] CLIENT DISCONNECTED [!]\n");
            close(client_socket->client_socket);
            free(client_socket);
        }

        if (bytes_received < 0) 
        {
            fprintf(stderr, "[x] RECEIVE [FAILED]\n");
            free(client_socket);
        }
        buffer[bytes_received] = '\0';

        printf("Received %zu bytes from client\n", bytes_received);

        printf("[CLIENT]=> %s\n", buffer);
    
        // Echo message back to client.
        bytes_sent = send(client_socket->client_socket, buffer, strlen(buffer), 0);
        if (bytes_sent < 0)
        {
            fprintf(stderr, "[x] SENDING [FAILED]\n");
            free(client_socket);
        }

        printf("Sent %zu bytes to client\n", bytes_sent);

    }
    close(client_socket->client_socket);
    free(client_socket);
}

