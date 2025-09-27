#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define QUEUE_SIZE 10
#define NUM_WORKERS 3
#define NUM_TASKS 20

typedef struct
{
    int items[QUEUE_SIZE];
    int front, rear, count;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} Queue;

Queue queue;

// ---- Queue functions ----
void queue_init(Queue *q)
{
    q->front = 0;
    q->rear = 0;
    q->count = 0;
    pthread_mutex_init(&q->mutex, NULL);
    pthread_cond_init(&q->cond, NULL);
}

void queue_enqueue(Queue *q, int item)
{
    pthread_mutex_lock(&q->mutex);

    // If full, just wait (to keep it simple)
    while (q->count == QUEUE_SIZE)
    {
        pthread_cond_wait(&q->cond, &q->mutex);
    }

    q->items[q->rear] = item;
    q->rear = (q->rear + 1) % QUEUE_SIZE;
    q->count++;

    pthread_cond_broadcast(&q->cond); // wake up waiting workers
    pthread_mutex_unlock(&q->mutex);
}

int queue_dequeue(Queue *q)
{
    pthread_mutex_lock(&q->mutex);

    // Wait until there is something to consume
    while (q->count == 0)
    {
        pthread_cond_wait(&q->cond, &q->mutex);
    }

    int item = q->items[q->front];
    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;

    pthread_cond_broadcast(&q->cond); // wake up possible producers
    pthread_mutex_unlock(&q->mutex);

    return item;
}

// ---- Worker thread ----
void *worker(void *arg)
{
    long id = (long)arg;

    while (1)
    {
        int task = queue_dequeue(&queue);
        printf("Worker %ld processing task %d\n", id, task);
        usleep(100000); // simulate work
    }
    return NULL;
}

int main()
{
    pthread_t workers[NUM_WORKERS];
    queue_init(&queue);

    // Start worker threads
    for (long i = 0; i < NUM_WORKERS; i++)
    {
        pthread_create(&workers[i], NULL, worker, (void *)i);
    }

    // Main thread produces tasks
    for (int i = 1; i <= NUM_TASKS; i++)
    {
        printf("Main thread enqueuing task %d\n", i);
        queue_enqueue(&queue, i);
        usleep(50000); // slow producer
    }

    // Join workers (infinite loop in this demo, so unreachable)
    for (int i = 0; i < NUM_WORKERS; i++)
    {
        pthread_join(workers[i], NULL);
    }

    return 0;
}
