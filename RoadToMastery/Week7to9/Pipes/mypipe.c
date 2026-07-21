// Reproduce: "echo hello | wc".

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
    // Command.
    char command[] = "echo";
    char *args[] = {"echo", "hello", NULL};

    pid_t pid = fork();
    if (pid == 0)
    {
        close(fd[0]);
        printf("Child closed fd %d\n", fd[0]);

        dup2(fd[1], 1);

        close(fd[1]);
        // execute the command.
        if (execvp(command, args) == -1)
        {
            fprintf(stderr, "[x] Exec! [FAILED]\n");
            exit(1);
        }

    }
    else {
        close(fd[1]);
        printf("Parent closed fd %d\n", fd[1]);

        dup2(fd[0], 0);

        char command2[] = "wc";
        char *args[] = {"wc", NULL};
        
        close(fd[0]);
        // execute the command.
        if (execvp(command2, args) == -1)
        {
            fprintf(stderr, "[x] Exec! [FAILED]\n");
            exit(1);
        }

    }
   
    return EXIT_SUCCESS;
}
