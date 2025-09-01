#include "utils.h"
#include <ctype.h>
#include <stdlib.h>

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


