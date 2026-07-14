// Write a program that: Calls fork(), Prints the PID of the parent, Prints the PID of the child.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
    pid_t pid, ppid;
    ppid = getpid();
    pid = fork();
    if (pid == 0) {
       printf("Parent Process ID => %d\n", ppid);
    }
    else {
        printf("Child Process ID => %d\n", pid);

        // Wait child process to finish.
        pid_t dpid = wait(NULL);
        printf("Die child process => %d\n", dpid); 
    }
    
    
    return EXIT_SUCCESS;
}
