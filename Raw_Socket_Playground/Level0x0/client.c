/*
    Client For The Simple Echo Server Program.
*/

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"

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

    // Create the server socket.
    int client_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client_sock < 0)
    {
        perror("[x] Socket Creation! [FAILED]");
        exit(EXIT_FAILURE);
    }
    printf("[+] Client Socket Created!: FD %d [SUCCESS]\n", client_sock);

    // Define the server address structure.
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    socklen_t server_addr_len = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr.s_addr);

    // Connect to the server.
    if (connect(client_sock, (struct sockaddr *)&server_addr, server_addr_len) <
        0)
    {
        perror("[x] Connect! [FAILED]");
        exit(EXIT_FAILURE);
    }
    printf("[+] Connected! [SUCCESS]\n");

    char buffer[1024];
    ssize_t bytes_received;

    // Receive server message.
    while ((bytes_received = recv(client_sock, buffer, sizeof(buffer) - 1, 0)) > 0)
    {
        if (bytes_received == 0)
        {
            perror("[-] Server! [DISCONNECTED]");
            exit(EXIT_FAILURE);
        }
        buffer[bytes_received] = '\0';
        printf("[+] %s [Server-Echo]\n", buffer);

        // Send message to the server.
        char message[1024];
        printf("Client:$=> ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        ssize_t bytes_sent = send(client_sock, message, strlen(message), 0);
        if (bytes_sent < 0)
        {
            perror("[x] Sending! [FAILED]");
            exit(EXIT_FAILURE);
        }
        printf("[+] Sent [SUCCESS]\n");
    }

    close(client_sock);

    return EXIT_SUCCESS;
}
