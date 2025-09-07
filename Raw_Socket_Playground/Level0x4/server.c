/*
 ** GROUP CHAT SERVER **
 */

#include "utils.h"
#include <arpa/inet.h>
#include <asm-generic/errno-base.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 4096

int server_sock;

// Mutual Exclusive Lock for shared file descriptor.
pthread_mutex_t mutexFD = PTHREAD_MUTEX_INITIALIZER;

// Shared: file descriptor for logging chat, number of clients online and
// array to store connected client's socket.
int file_D, numOfClients, client_sockets[MAX_CLIENTS];

// Use a signal-safe flag to trigger shutdown instead of exiting in handler.
static volatile sig_atomic_t g_stop = 0;

// Struct to store client.
typedef struct
{
    int client_socket;
} Client_Args;

// Function Prototype.
void *handle_client(void *args);
void handle_sigint(int sig);
int remove_client(int client_socket);
int log_chat(char *chat, int written_len);
int broadcast_chat(char *chat, int written_len, int sender);

int main(int argc, char *argv[])
{
    // Install handler before doing work.
    struct sigaction sa = {0};
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

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

    // Allow quick restarts.
    int optval = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &optval,
                   sizeof(optval)) < 0)
    {
        fprintf(stderr, "[x] setsockopt(SO_REUSEADDR) [FAILED]\n");
        // Not fatal; continue.
    }

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
    int client_sock, threadId;
    pthread_t client_thread;

    // Initialize number of clients online to 0.
    numOfClients = 0;

    // Zero out the client_sockets array.
    memset(client_sockets, 0, sizeof(client_sockets));

    // Open file for writing.
    const char *file = ".chat.txt";
    file_D = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);

    while (!g_stop)
    {

        client_sock = accept(server_sock, (struct sockaddr *)&client_addr,
                             &client_addr_len);
        if (client_sock < 0)
        {
            if (errno == EINTR)
            {
                // Interrupted by signal; try again unless stopping.
                if (g_stop)
                {
                    break;
                }
                continue; // Retry accept()...
            }

            // If shutdown closed the socket, accept will fail. Exit loop cleanly.
            if (g_stop || errno == EBADF)
            {
                break;
            }

            fprintf(stderr, "[x] Accept! [FAILED]\n");
            // Continue rather than exit the whole process.
            continue;
        }

        // Log client address safely with inet_ntop (thread-safe).
        char addrbuf[INET_ADDRSTRLEN];
        const char *ip =
            inet_ntop(AF_INET, &client_addr.sin_addr, addrbuf, sizeof(addrbuf));
        if (!ip)
            ip = "unknown";
        printf("[+] New Client Online: FD %d [%s:%d]\n", client_sock, ip,
               ntohs(client_addr.sin_port));

        // Store connected client's socket in the client_sockets array.
        int placed_index = -1;
        pthread_mutex_lock(&mutexFD);
        if (numOfClients < MAX_CLIENTS)
        {
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (client_sockets[i] == 0)
                {
                    client_sockets[i] = client_sock;
                    numOfClients += 1; // Increment number of clients online.
                    placed_index = i;
                    break;
                }
            }
        }
        printf("[#] Clients Online =>[%d]\n", numOfClients);
        pthread_mutex_unlock(&mutexFD);

        // If we couldn't place the client (server full), reject
        // gracefully.
        if (placed_index == -1)
        {
            const char *busy = "Server busy. Try again later.\n";
            (void)send(client_sock, busy, strlen(busy), 0);
            close(client_sock);
            continue;
        }

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
        threadId = pthread_create(&client_thread, NULL, handle_client,
                                  (void *)client_args);
        if (threadId != 0)
        {
            fprintf(stderr, "[x] Pthread Create! [FAILED]\n");
            free(client_args);
            exit(EXIT_FAILURE);
        }

        // Detach thread to prevent resource leaks.
        pthread_detach(client_thread);
    }

    // Cleanup
    if (file_D >= 0)
        close(file_D);
    if (server_sock >= 0)
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
    char buffer[BUFFER_SIZE], chat[BUFFER_SIZE];
    ssize_t bytes_received;

    // Receive client's chat.
    while (1)
    {
        bytes_received =
            recv(client->client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == 0)
        {
            fprintf(stderr, "[-] Client! [DISCONNECTED]\n");

            // Remove client socket.
            remove_client(client->client_socket);

            // Clean up resources.
            close(client->client_socket);
            free(client);
            return NULL;
        }
        else if (bytes_received < 0)
        {
            if (errno == EINTR)
                continue; // Retry on signal
            fprintf(stderr, "[x] Receive! [FAILED] (errno=%d)\n", errno);

            // Remove client socket.
            remove_client(client->client_socket);

            // Clean up resources.
            close(client->client_socket);
            free(client);
            return NULL;
        }

        buffer[bytes_received] = '\0';

        // Format the client chat for logging.
        int written_len =
            snprintf(chat, sizeof(chat), "%s [HH:MM]", buffer);
        if (written_len < 0)
        {
            // formatting error; skip write this round
            continue;
        }
        if ((size_t)written_len >= sizeof(chat))
        {
            // truncated; ensure newline
            chat[sizeof(chat) - 2] = '\n';
            chat[sizeof(chat) - 1] = '\0';
            written_len = (int)strlen(chat);
        }

        // Log the client's message.
        log_chat(chat, written_len);

        // printf("[+] Received %zu bytes from client [%s]\n", bytes_received,       buffer);

        // Broadcast chat to other clients.
        broadcast_chat(chat, written_len, client->client_socket);
    }

    close(client->client_socket);
    free(client);
    return NULL;
}

// Graceful shutdown handling.
void handle_sigint(int sig)
{
    (void)sig;

    // Just set a flag and close the listening socket to unblock accept().
    g_stop = 1;

    // Async-signal-safe calls only:
    if (server_sock >= 0)
        close(server_sock);
    if (file_D >= 0)
        close(file_D);

    // main() will finish cleanup after accept() unblocks.
}
// Function to remove disconnected clients.
int remove_client(int client_socket)
{
    // Remove client_sock from the client_sockets[] array.
    pthread_mutex_lock(&mutexFD);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        if (client_sockets[i] == client_socket)
        {
            client_sockets[i] = 0;
            // Decrement number of clients online.
            numOfClients -= 1;
            break;
        }
    }
    printf("[#] Clients Online =>[%d]\n", numOfClients);
    pthread_mutex_unlock(&mutexFD);
    return g_stop;
}

// Function to log clients chat.
int log_chat(char *chat, int written_len)
{
    // Handle partial writes and errors.
    pthread_mutex_lock(&mutexFD);
    const char *p = chat;
    ssize_t to_write = written_len;
    while (to_write > 0)
    {
        ssize_t w = write(file_D, p, (size_t)to_write);
        if (w < 0)
        {
            if (errno == EINTR)
                continue;
            fprintf(stderr, "[x] write() failed (errno=%d)\n", errno);
            break;
        }
        p += w;
        to_write -= w;
    }
    write(file_D, "\n", sizeof(char));
    pthread_mutex_unlock(&mutexFD);

    return g_stop;
}

// Function to broadcast client's chat to other clients.
int broadcast_chat(char *chat, int written_len, int sender)
{
    pthread_mutex_lock(&mutexFD);
    for (int i = 0; i < numOfClients; i++)
    {
        if (client_sockets[i] != 0 && client_sockets[i] != sender)
        {
            ssize_t bytes_sent = send(client_sockets[i], chat, written_len, 0);
            if (bytes_sent < 0)
            {
                fprintf(stderr, "[x] Sending! [FAILED]\n");
            }
            printf("[+] Sent %zu bytes to client [SUCCESS]\n", bytes_sent);
        }
    }
    pthread_mutex_unlock(&mutexFD);
    return g_stop;
}
