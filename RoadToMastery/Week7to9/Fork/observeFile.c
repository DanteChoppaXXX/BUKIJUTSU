// Write a program that: Open a file before calling fork(), Observe that both processes inherit the descriptor.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(void)
{
    pid_t pid, ppid;
    ppid = getpid();
    // Open a file.
    int fd = open("./callfork.c", O_RDONLY);
    if (fd < 0) {
        fprintf(stderr, "[x] File Open! [FAILED]\n");
        exit(1);
    }

    // Create a child process.
    pid = fork();

    if (pid == 0) {
       printf("Parent Process ID => %d\n", ppid);
       printf("FD => %d\n", fd);
    }
    else {
        printf("Child Process ID => %d\n", pid);
        printf("FD => %d\n", fd);

        // Wait child process to finish.
        pid_t dpid = wait(NULL);
        printf("Die child process => %d\n", dpid); 
    }
    
    close(fd); 
    return EXIT_SUCCESS;
}

