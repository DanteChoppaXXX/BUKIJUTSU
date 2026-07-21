// Create a pipe: Write from one end and Read from the other end.

#include <stdio.h>
#include <stdlib.h>
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

    // Write from one end.
    const char message[] = "Pipeline 101";
    write(fd[1], message, strlen(message));

    // Read from the other end.
    char buffer[64];
    read(fd[0], buffer, sizeof(buffer));

    printf("Pipeline Message => %s\n", buffer);

    close(fd[0]);
    close(fd[1]);
    return EXIT_SUCCESS;
}
