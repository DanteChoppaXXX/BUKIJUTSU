// Allocate memory for an int, store something in there and print it.

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *digit = malloc(sizeof(int));

    // Check if allocation failed.
    if (digit == NULL)
    {
        perror("Memory Allocation Failed!");
        return EXIT_FAILURE;
    }
    
    // Store something in allocated memory.
    *digit = 419;

    // Print the stored integer.
    printf("Allocated Memory Holds The Value => %d\n", *digit);

    free(digit);

    return EXIT_SUCCESS;
}
