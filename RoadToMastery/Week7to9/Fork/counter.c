// Write a program that: Opens a file, stores int counter = 0, calls fork(), and then both parent and child increment counter and write to the file.
// Observe which data is shared and which is not.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <wait.h>

int main(void)
{
    int counter = 0;
    
    // Open a file for writing.
    int fd = open("./counter.txt", O_WRONLY|O_CREAT|O_APPEND, S_IWUSR|S_IRUSR);
    if (fd < 0) {
        fprintf(stderr, "[x] File Open! [FAILED]\n");
        exit(1);
    }

    // Store the value of counter in the file.
    dprintf(fd, "%d\n", counter);

    // Create child process.
    pid_t pid = fork();

    if (pid == 0) {
        counter++;
        dprintf(fd, "Child increment counter to %d\n", counter);
        printf("Child Process increment counter by 1 => %d\n", counter);
    }
    else {
        counter += 2;
        dprintf(fd, "Parent increment counter to %d\n", counter);
        printf("Parent Process increment counter by 2 => %d\n", counter);

        // Wait for the child process to finish.
        pid_t dpid = wait(NULL);
        printf("Die Child Process => %d\n", dpid);
    }

    printf("Counter => %d\n", counter);

    close(fd);
    return EXIT_SUCCESS;
}
