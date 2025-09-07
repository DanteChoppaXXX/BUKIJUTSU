#include "utils.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Function to get and Validate port number.
int get_port(const char *string)
{
    // Ensure only digits.
    for (const char *port = string; *port; port++)
    {
        if (!isdigit((unsigned char)*port))
        {
            return -1;
        }
    }

    // Convert and check range.
    int port = atoi(string);
    return (port >= 1 && port <= 65535) ? port : -1;
}

// Username validation function.
UsernameStatus validate_username(const char *username, int min_len, int max_len)
{
    if (username == NULL)
    {
        return USERNAME_NULL;
    }

    int len = strlen(username);

    if (len < min_len)
    {
        return USERNAME_TOO_SHORT;
    }
    if (len > max_len)
    {
        return USERNAME_TOO_LONG;
    }

    if (!isalpha((unsigned char)username[0]))
    {
        return USERNAME_INVALID_START;
    }

    for (int i = 1; i < len; i++)
    {
        if (!(isalnum((unsigned char)username[i]) || username[i] == '_'))
        {
            return USERNAME_INVALID_CHAR;
        }
    }

    return USERNAME_VALID;
}
