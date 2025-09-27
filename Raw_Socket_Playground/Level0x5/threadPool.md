Nice — you’ve done a lot of work already and I can see you’re moving the design in the right direction (queue, fixed pool, reuse of broadcast/logging). Great instincts.

I read through your Step-2 draft and annotated the *important* problems (logic bugs, race/ordering issues, API/signature mismatches) and then gave corrected/safer implementations you can drop into your code. Fixing these will make the thread-pool server robust and predictable.

---

# High-level issues I found

1. **Queue implementation is incorrect** (several logic errors):

   * `queue_init` sets fields wrongly (`queue->front = queue->rear; queue->rear = queue->count;`) — uses uninitialised values.
   * `queue_enqueue` writes `queue->rear = client_sock;` instead of storing into the `sockets[]` array.
   * `queue_enqueue` increments `queue->count` but does not `unlock` before returning when queue full; also does not `return` after dropping.
   * `queue_dequeue` returns `queue->front` instead of `sockets[front]`, and **increments** `count` instead of decrementing it.
   * `pthread_mutex_init` / `pthread_cond_init` checks are inverted (you check `if (!pthread_mutex_init(...))` and then print error; `pthread_*_init` returns 0 on success).

2. **Function signature mismatch / incorrect usage**

   * `void *handle_client(int client_socket);` — this signature is wrong for two reasons:

     * `handle_client` is declared returning `void *` but it semantically returns nothing / uses `return NULL;` — mixed.
     * You're calling `handle_client(client_socket);` from a worker (synchronous call). Decide: `handle_client` should be `void handle_client(int)` (no pthread wrapper) or keep old `void *handle_client(void *args)` pattern and adapt worker to call it with a heap-allocated arg and `pthread_create`. The cleanest: make it `void handle_client(int client_socket)` (no thread return value).

3. **Ordering race between enqueue and registering client in `client_sockets[]`**

   * You `queue_enqueue(conn_queue, client_sock);` then register the socket into `client_sockets[]`. If `queue_enqueue` drops (queue full), you close socket — but you still register it afterwards. This will leave a closed FD in `client_sockets[]`.
   * Fix: register the socket (under `mutexFD`) **before** enqueue, or make `queue_enqueue` block instead of dropping, or have `queue_enqueue` return a status so the caller can decide.

4. **Shutdown handling for workers**

   * When `g_stop` is set, workers might be blocked in `pthread_cond_wait`. You need to `pthread_cond_broadcast` in the shutdown path so workers wake, or enqueue sentinel `-1` values that signal them to exit. Otherwise they may hang forever.

5. **Missing checks / error handling**

   * `open()` return value not checked.
   * `pthread_create` return values not checked.

6. **Minor style / consistency**

   * `fprintf(stderr, "[x] Sending! [FAILED]\n");` could include `strerror(errno)` for better debug.
   * Consider splitting the mutex for `client_sockets[]` and the log file if you want finer-grained concurrency later.

---

# Concrete fixes — copyable snippets

Below are corrected implementations for the queue API, worker loop, and a suggested `handle_client` signature and related main changes. These are minimal, correct, and designed to fit with your current architecture.

### 1) Correct `ConnQueue` functions

```c
/* queue_init: set front/rear/count and init sync primitives */
void queue_init(ConnQueue *queue)
{
    queue->front = 0;
    queue->rear = 0;
    queue->count = 0;

    if (pthread_mutex_init(&queue->mutex, NULL) != 0) {
        fprintf(stderr, "[-] pthread_mutex_init failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pthread_cond_init(&queue->cond, NULL) != 0) {
        fprintf(stderr, "[-] pthread_cond_init failed: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}
```

```c
/* queue_enqueue: returns 0 on success, -1 if dropped */
int queue_enqueue(ConnQueue *queue, int client_sock)
{
    pthread_mutex_lock(&queue->mutex);

    if (queue->count >= QUEUE_SIZE) {
        /* queue full -> drop and close socket */
        pthread_mutex_unlock(&queue->mutex);
        const char *busy = "Server busy. Try again later.\n";
        send(client_sock, busy, strlen(busy), 0);
        close(client_sock);
        return -1;
    }

    queue->sockets[queue->rear] = client_sock;
    queue->rear = (queue->rear + 1) % QUEUE_SIZE;
    queue->count++;

    /* wake one worker */
    pthread_cond_signal(&queue->cond);
    pthread_mutex_unlock(&queue->mutex);
    return 0;
}
```

```c
/* queue_dequeue: blocks until an item available OR g_stop is set.
   Returns >=0 socket; returns -1 if shutdown requested and no sockets. */
int queue_dequeue(ConnQueue *queue)
{
    pthread_mutex_lock(&queue->mutex);

    while (queue->count == 0 && !g_stop) {
        pthread_cond_wait(&queue->cond, &queue->mutex);
    }

    if (queue->count == 0 && g_stop) {
        /* no items and shutting down */
        pthread_mutex_unlock(&queue->mutex);
        return -1;
    }

    int sock = queue->sockets[queue->front];
    queue->front = (queue->front + 1) % QUEUE_SIZE;
    queue->count--;

    pthread_mutex_unlock(&queue->mutex);
    return sock;
}
```

Notes:

* I made `queue_enqueue` return a status; this helps main avoid registering a dropped socket into `client_sockets[]`.
* `queue_dequeue` returns `-1` on shutdown so worker threads can exit their loop cleanly.

---

### 2) `handle_client` signature (synchronous call from worker)

Change your `handle_client` to **synchronous** function that just receives the socket and returns `void` (or int). Example:

```c
/* handle_client: synchronous; called directly by worker threads */
void handle_client(int client_socket)
{
    const char *message = "Welcome To The Dojo! Warrior\n";
    ssize_t bytes_sent = send(client_socket, message, strlen(message), 0);
    if (bytes_sent < 0) {
        fprintf(stderr, "[x] Sending welcome failed: %s\n", strerror(errno));
        close(client_socket);
        return;
    }

    char buffer[BUFFER_SIZE];
    char chat[BUFFER_SIZE+64];
    ssize_t bytes_received;

    while (1) {
        bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == 0) {
            /* clean disconnect */
            remove_client(client_socket);
            close(client_socket);
            return;
        } else if (bytes_received < 0) {
            if (errno == EINTR) continue;
            fprintf(stderr, "[x] recv() failed: %s\n", strerror(errno));
            remove_client(client_socket);
            close(client_socket);
            return;
        }

        buffer[bytes_received] = '\0';

        int written_len = snprintf(chat, sizeof(chat), "%s", buffer);
        if (written_len < 0) continue;
        if ((size_t)written_len >= sizeof(chat)) {
            chat[sizeof(chat)-2] = '\n';
            chat[sizeof(chat)-1] = '\0';
            written_len = (int)strlen(chat);
        }

        log_chat(chat, written_len);
        broadcast_chat(chat, written_len, client_socket);
    }
}
```

Then in `worker_thread`, call it:

```c
void *worker_thread(void *arg)
{
    ConnQueue *queue = (ConnQueue *)arg;

    while (!g_stop) {
        int client_socket = queue_dequeue(queue);
        if (client_socket == -1) break; /* shutdown */
        handle_client(client_socket);
    }
    return NULL;
}
```

---

### 3) Main thread ordering: register before enqueue (recommended)

To avoid the race where `queue_enqueue` might drop a socket but main still registers it, *register the client in `client_sockets[]` first*, then enqueue. Example:

```c
/* after accept() succeeded */
int placed_index = -1;

/* try to reserve a slot in client_sockets[] under mutex */
pthread_mutex_lock(&mutexFD);
if (numOfClients < MAX_CLIENTS) {
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        if (client_sockets[i] == 0) {
            client_sockets[i] = client_sock; /* reserve */
            numOfClients++;
            placed_index = i;
            break;
        }
    }
}
pthread_mutex_unlock(&mutexFD);

if (placed_index == -1) {
    const char *busy = "Server busy. Try again later.\n";
    send(client_sock, busy, strlen(busy), 0);
    close(client_sock);
    continue;
}

/* Now enqueue; if enqueue fails (queue full), remove reservation */
if (queue_enqueue(conn_queue, client_sock) != 0) {
    /* enqueue dropped/closed the socket, undo registration */
    remove_client(client_sock); /* under mutex */
    continue;
}
```

This ensures `client_sockets[]` only contains valid sockets.

---

### 4) Shutdown: wake workers & let them exit

When you set `g_stop = 1` in the sig handler, broadcast the cond var so waiting workers wake up. Because signal handlers must call only async-signal-safe functions, don't broadcast there directly. Instead, in the main thread after catching `g_stop`, call:

```c
/* after accept loop breaks in main() */
pthread_mutex_lock(&conn_queue->mutex);
pthread_cond_broadcast(&conn_queue->cond); /* wake all workers */
pthread_mutex_unlock(&conn_queue->mutex);

/* optionally join threads */
for (int i = 0; i < MAX_THREADS; ++i) {
    pthread_join(threads[i], NULL);
}
```

Also, `handle_sigint` in your current code closes `server_sock` and `file_D` — that's fine, but keep the cond broadcast in main (not in handler).

---

### 5) Misc fixes / improvements

* Check `open()` result for `file_D < 0` and log `strerror(errno)`.
* Check `pthread_create` return values for worker threads and handle failure.
* When printing `strerror(errno)` inside signal handler — avoid calling non-async safe functions there; keep handler minimal (you already do).
* Prefer `ssize_t` for read/write sizes.
* Consider validating that `send()` writes full length; but for ordinary sockets/send, partial sends are possible — if you want to guarantee full send on broadcast, implement a `send_all(int fd, const void *buf, size_t len)` wrapper that loops until all sent or error.
* Consider switching `client_sockets[]` initial value to -1 instead of 0 if you worry about FD 0 (stdin) confusion, but since sockets are >= 3 usually it's fine — you already use 0 as empty which is consistent.

---

# Suggested next steps for you (learning path)

1. Apply the queue fixes above (implement `queue_enqueue`, `queue_dequeue`, `queue_init` as shown).
2. Change `handle_client` to be synchronous `void handle_client(int)` and update worker to call it as shown.
3. Change the main ordering: reserve slot in `client_sockets[]` before enqueue; if enqueue fails, undo reservation.
4. Add graceful shutdown: after accept loop exits, `pthread_cond_broadcast`, join worker threads, close remaining client sockets under mutex, close file, exit.
5. Test:

   * Normal multi-client chat.
   * Flood accept to force queue full; ensure server drops cleanly and doesn't register closed FDs.
   * Ctrl+C shutdown: ensure workers exit and process terminates cleanly.
6. (Optional) Implement `send_all()` to handle partial `send()` results in `broadcast_chat()`.

---

# Small checklist for you to confirm once you apply changes

* [ ] `queue_init` sets front/rear/count to 0.
* [ ] `enqueue` writes into `sockets[rear]`, updates `rear`, updates `count`, signals cond.
* [ ] `dequeue` reads from `sockets[front]`, updates `front`, decrements `count`.
* [ ] `handle_client` signature matches how worker calls it.
* [ ] `client_sockets[]` is updated under mutex before enqueue OR enqueue returns success before registration.
* [ ] On shutdown, cond is broadcast and workers exit.

---
