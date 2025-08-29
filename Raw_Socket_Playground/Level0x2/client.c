
/*
    Client For Multi-Client Server Program.
*/

#include "utils.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"

// Function Prototype.
void *handle_receive(void *args);
void *handle_send(void *args);

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
        fprintf(stderr, "[x] Socket Creation! [FAILED]\n");
        exit(EXIT_FAILURE);
    }
    printf("[+] Client Socket Created!: FD %d [SUCCESS]\n", server_sock);

    // Define the server address structure.
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    socklen_t server_addr_len = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr.s_addr) < 0)
    {
        fprintf(stderr, "[x] Invalid Address: %s [FAILED]\n", SERVER_IP);
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Connect to the server.
    if (connect(server_sock, (struct sockaddr *)&server_addr, server_addr_len) <
        0)
    {
        fprintf(stderr, "[x] Connect! [FAILED]\n");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    // printf("[+] Connected! [SUCCESS]\n");
    char buffer[1024];
    ssize_t bytes_received;

    // Receive incoming messages from the server.
    bytes_received = recv(server_sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received < 0)
    {
        fprintf(stderr, "[x] Receive! [FAILED]\n");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_received] = '\0';
    printf("[+] %s [CONNECTED!]\n", buffer);

    // Create two threads (1) for sending messages (2) for receiving messages.
    pthread_t send_thread, receive_thread;
    int pthread1, pthread2;

    // Create sending thread.
    pthread1 = pthread_create(&send_thread, NULL, handle_send,
                              (void *)&server_sock);
    if (pthread1 != 0)
    {
        fprintf(stderr, "[x] Pthread Create! [FAILED]\n");
        close(server_sock);
        exit(EXIT_FAILURE);
    }
    // Create receive thread.
    pthread2 = pthread_create(&receive_thread, NULL, handle_receive,
                              (void *)&server_sock);
    if (pthread2 != 0)
    {
        fprintf(stderr, "[x] Pthread Create! [FAILED]\n");
        close(server_sock);
        exit(EXIT_FAILURE);
    }

    // Wait for the threads to finish execution.
    pthread_join(send_thread, NULL);
    pthread_detach(receive_thread);

    close(server_sock);
    return EXIT_SUCCESS;
}

// Function for receiving message.
void *handle_receive(void *args)
{
    int *server_sock = (int *)args;
    char buffer[1024];
    ssize_t bytes_received;

    // Receive incoming messages from the server.
    while ((bytes_received = recv(*server_sock, buffer, sizeof(buffer) - 1, 0)) >
           0)
    {
        if (bytes_received == 0)
        {
            fprintf(stderr, "[-] Server! [DISCONNECTED]\n");
            close(*server_sock);
            exit(EXIT_FAILURE);
        }
        buffer[bytes_received] = '\0';
        printf("\033[A\r");
        printf("[+] %s [Server-Echo]\n\n", buffer);
    }

    return NULL;
}

// Function for sending message.
void *handle_send(void *args)
{
    int *server_sock = (int *)args;

    // Send message to the server.
    char message[1024];

    while (0x1)
    {
        printf("\nClient:$=> ");

        if (fgets(message, sizeof(message), stdin) == NULL)
        {
            break;
        }

        //  Check if user typed exit command.
        if (strcmp(message, "exit\n") == 0)
        {
            printf("[-] Exiting Dojo... [Zzz]\n");
            close(*server_sock);
            exit(EXIT_SUCCESS);
        }

        // Check if user pressed enter without typing anything OR typed only
        // spaces or tabs.
        if (strspn(message, " \t\n") == strlen(message))
        {
            continue;
        }

        message[strcspn(message, "\n")] = '\0';

        ssize_t bytes_sent = send(*server_sock, message, strlen(message), 0);
        if (bytes_sent < 0)
        {
            fprintf(stderr, "[x] Sending! [FAILED]\n");
            exit(EXIT_FAILURE);
        }
        printf("[+] Sent [SUCCESS]\n");
    }

    return NULL;
}
