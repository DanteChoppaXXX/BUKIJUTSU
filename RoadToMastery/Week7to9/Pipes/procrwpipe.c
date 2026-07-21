
// Create a pipe: Call fork(), Parent writes, Child reads.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
    // Create a pipe.
    int fd[2];

    if (pipe(fd) == -1)
    {
        fprintf(stderr, "[x] Pipe Creation! [FAILED]\n");
        exit(1);
    }
    // Print the descriptor numbers.
    printf("Pipe Descriptor 1 => %d\n", fd[0]);
    printf("Pipe Descriptor 2 => %d\n", fd[1]);

    pid_t pid = fork();
    if (pid == 0)
    {
        close(fd[1]);
        printf("Child closed fd %d\n", fd[1]);

        // Read from the other end.
        char buffer[64];
        read(fd[0], buffer, sizeof(buffer));

        printf("Pipeline Message => %s\n", buffer);

        // Close the file descriptor.
        close(fd[0]);
        printf("Child closed fd %d\n", fd[0]);
 
    }
    else {
        close(fd[0]);
        printf("Parent closed fd %d\n", fd[0]);

        // Write from one end.
        const char message[] = "Hello Child!";
        write(fd[1], message, strlen(message)); 

        // Close the file descriptor.
        close(fd[1]);
        printf("Parent closed fd %d\n", fd[1]);
    }
   
    return EXIT_SUCCESS;
}
