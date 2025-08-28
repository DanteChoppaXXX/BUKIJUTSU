Sure! Here's a **clean, actionable list of improvements and corrections** in plain text format that you can reference while updating your code:

---

### ✅ **Necessary Improvements & Corrections**

#### 1. **Fix `handle_client` Thread Function Signature**

* Change:

  ```c
  void handle_client(void *args)
  ```

  To:

  ```c
  void *handle_client(void *args)
  ```
* Add a `return NULL;` at the end of the function.

---

#### 2. **Pass Full `Client_Args` Struct to Thread**

* Change this:

  ```c
  pthread_create(&client_thread, NULL, (void *)&handle_client, (void *)&client_args->client_socket);
  ```
* To this:

  ```c
  pthread_create(&client_thread, NULL, handle_client, (void *)client_args);
  ```

---

#### 3. **Free Allocated Memory After Thread Finishes**

* In `handle_client()`:

  ```c
  close(client_sock->client_socket);
  free(client_sock);
  ```

---

#### 4. **Use `pthread_detach()` to Avoid Resource Leaks**

* After `pthread_create()`:

  ```c
  pthread_detach(client_thread);
  ```

---

#### 5. **Avoid Using `exit()` Inside Threads**

* Replace all `exit()` calls inside `handle_client()` with proper cleanup and `return NULL;`.

---

#### 6. **Increase `listen()` Backlog**

* Change:

  ```c
  listen(server_sock, 1);
  ```
* To:

  ```c
  listen(server_sock, MAX_CLIENTS);
  ```

---

#### 7. **Fix Memory Leak in Main Loop**

* If `pthread_create()` fails, free `client_args` before exiting:

  ```c
  free(client_args);
  ```

---

#### 8. **Improve Main Loop Readability**

* Replace `while (0x1)` with:

  ```c
  while (1)
  ```

---

#### 9. **Optional: Log Client IP Address**

* Inside the accept block:

  ```c
  char *client_ip = inet_ntoa(client_addr.sin_addr);
  printf("[+] New Client Connected: %s:%d\n", client_ip, ntohs(client_addr.sin_port));
  ```

---

#### 10. **Graceful Shutdown (Optional Enhancement)**

* Add `signal(SIGINT, handler)` to handle Ctrl+C and gracefully close `server_sock`.

---

Let me know if you want a corrected version of the full code with all these applied.

