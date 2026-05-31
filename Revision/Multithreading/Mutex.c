#include <stdio.h>
#include <threads.h>

mtx_t serial_mtx;   // <--- MUTEX VARIABLE

int run(void *arg)
{
    (void)arg;

    static int serial = 0;  // Shared static variable!
    // Acquire the mutex -- all thread will block on this call until they get the lock:

    mtx_lock(&serial_mtx);      // <-- ACQUIRE MUTEX 
    printf("Thread running! %d\n", serial);

    serial++;

    // Done getting and setting the data, so free the lock. This will unblock threads on the mtx_lock() call:

    mtx_unlock(&serial_mtx);    // <-- RELEASE MUTEX  

    return 0;
}

#define THREAD_COUNT 10

int main(void)
{
    thrd_t t[THREAD_COUNT];

    // Initialize the mutex variable, indicating this is a normal no-frills, mutex:
    
    mtx_init(&serial_mtx, mtx_plain);       // <-- CREATE MUTEX  

    for (int i = 0; i < THREAD_COUNT; i++) {
    
        thrd_create(t + i, run, NULL);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
    
        thrd_join(t[i], NULL);
    }

    // Done with the mutex destroy it:

    mtx_destroy(&serial_mtx);       // <--- DESTROY MUTEX   
}
