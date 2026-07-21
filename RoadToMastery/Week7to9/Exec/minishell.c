// Write a program that: Calls fork(), Calls exec() in the child, Calls wait() in the parent.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
    char command[] = "ls";
    char *args[] = {"ls", "-l", NULL};
    pid_t pid = fork();
    
    if (pid == 0)
    {
        printf("Before exec [child]\n");
        if (execvp(command, args) == -1)
        {
            fprintf(stderr, "[x] Exec! [FAILED]\n");
            exit(1);
        }
    }
    else {
        wait(NULL);
        printf("After exec [parent]\n");
    }

    return EXIT_SUCCESS;
}
