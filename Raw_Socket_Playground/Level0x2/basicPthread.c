/*
    Basic Pthread implementation for learning purpose.
    Goal: Write a program that executes a function in separate threads.
    Extra: Retrive and display the return value of the pthread_create() function
   (usually 0 if successful).
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Function Prototype.
void greet(void *args);

int main()
{
    // Declare two threads.
    pthread_t thread1, thread2;

    // Initialize two const char* array with different messages.
    const char *message1 = "\033[1;32mThread 1";
    const char *message2 = "\033[1;33mThread 2";

    // Create two threads to execute the greet() function.
    int pthread1, pthread2;
    pthread1 = pthread_create(&thread1, NULL, (void *)&greet, (void *)message1);
    if (pthread1 != 0)
    {
        fprintf(stderr, "[x] Pthread Create! [FAILED]\n");
        exit(EXIT_FAILURE);
    }

    pthread2 = pthread_create(&thread2, NULL, (void *)&greet, (void *)message2);
    if (pthread2 != 0)
    {
        fprintf(stderr, "[x] Pthread Create! [FAILED]\n");
        exit(EXIT_FAILURE);
    }

    // Wait for the threads to finish execution.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Display the return value of the threads.
    printf("\033[1;32m[!] %s return value => [%d]\n", message1, pthread1);
    printf("\033[1;33m[!] %s return value => [%d]\n", message2, pthread2);

    return EXIT_SUCCESS;
}

// Greetings function.
void greet(void *args)
{
    const char *thread = (const char *)args;
    printf("\033[0m\033[1mGreetings From %s\n", thread);
}
