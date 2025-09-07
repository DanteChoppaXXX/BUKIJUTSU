#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>

int get_port(const char *string);

// Error codes for username validation
typedef enum {
    USERNAME_VALID = 0,        // Username is valid
    USERNAME_NULL,             // Input is NULL
    USERNAME_TOO_SHORT,        // Length < min_len
    USERNAME_TOO_LONG,         // Length > max_len
    USERNAME_INVALID_START,    // First char is not a letter
    USERNAME_INVALID_CHAR      // Contains invalid characters
} UsernameStatus;

// Validates a username and returns a UsernameStatus code.
// Rules:
//  - Length between min_len and max_len
//  - Starts with a letter
//  - Remaining chars can be letters, digits, or underscore
UsernameStatus validate_username(const char *username, int min_len, int max_len);

#endif // UTILS_H

