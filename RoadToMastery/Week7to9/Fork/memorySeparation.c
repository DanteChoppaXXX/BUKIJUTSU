// Write a program that: Initializes a variable 'x', modifies x in the child's process and prove that the parent's x does not change.

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    int x = 10;

    // Create a child process.
    pid_t pid = fork();
    if (pid == 0) {
        x = 20;
        printf("Child's Process x => %d\n", x);
    }
    else {
        printf("Parent's Process x => %d\n", x);
    }
    
    return EXIT_SUCCESS;
}
