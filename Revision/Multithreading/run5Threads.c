#include <stdio.h>
#include <threads.h>
#include <stdlib.h>

// This is the function the thread will run. It can be called anything.
//
// arg is the argument pointer passed to 'thrd_create()'.
//
// The parent thread will get the return value back from 'thrd_join()' later.

int run(void *arg)
{
    int i = *(int*)arg;

    free(arg);
    
    printf("THREAD %d: Running!\n", i);

    return i;
}

#define THREAD_COUNT 5

int main(void)
{
    thrd_t t[THREAD_COUNT];   // t will hold an array of thread IDs 
    int i;

    printf("Launching a thread\n");

    for (i = 0; i < THREAD_COUNT; i++) {
    
        int *arg = malloc(sizeof *arg);
        *arg = i;

        thrd_create(t + i, run, arg);
    }

    printf("Doing other things while the thread runs\n");

    printf("Waiting for thread to complete...\n");

    for (int i = 0; i < THREAD_COUNT; i++) {
    
        int res;    // Holds return value from the thread exit
        // Wait here for the thread to complete; store ther return value in res:
        thrd_join(t[i], &res);
        printf("Thread exited with return value %d\n", res);
    }

    printf("All threads complete!\n");
}
