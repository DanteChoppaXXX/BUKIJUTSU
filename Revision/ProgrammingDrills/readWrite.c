// Write a minimal program using read and write.
// This program will take user input into a buffer, write() the content into a file and then read() the content from the file.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(void){

    char buffer[1024];
    
    // Get user input.
    printf("Type a note: \n");
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n") + 1] = '\0';   // Null terminate the buffer.
    
    // Write the content of the buffer into a file.
    const char *filename = "note.txt";
    int fd = open(filename, O_WRONLY|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR);
    if (fd < 0) {
        perror("[x] Failed to open file! [x]");
    }

    ssize_t bytes_written;
    bytes_written = write(fd, buffer, strlen(buffer));
    if (bytes_written < 0) {
        perror("[x] Failed to write to file! [x]");
    }
    close(fd);
    
    printf("Wrote %zu bytes from buffer into file => [%s]\n", bytes_written, buffer);

    // Read the content of the file.
    char note[1024];

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("[x] Failed to open file! [x]");
    }

    ssize_t bytes_read;
    bytes_read = read(fd, note, bytes_written);
    if (bytes_read < 0) {
        perror("[x] Failed to read from file! [x]");
    }
    note[bytes_read] = '\0';  // Null terminate the buffer.
    close(fd);
    printf("Read %zu bytes from file into buffer => [%s]\n", bytes_read, note);

    return 0;
}
