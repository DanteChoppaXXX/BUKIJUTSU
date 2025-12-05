// Allocate memory for an array of integer, store somethings in there and print them.
// Calloc() is best for array cause it initializes the memory to zero.

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *digits = calloc(10, sizeof(int));

    // Check if allocation failed.
    if (digits == NULL)
    {
        perror("Memory Allocation Failed!");
        return EXIT_FAILURE;
    }
    
    // Store somethings in allocated memory.
    for (int i = 0; i < 10; i++)
    {
        digits[i] = i * 5;
    
    }

    // Print the stored integers.
    int *digit = digits; 

    for (int i = 0; i < 10; i++)
    {
        printf("Allocated Memory (%p) Holds The Values %d:\n", digit, digits[i]);
        digit++;
    }


    free(digits);

    return EXIT_SUCCESS;
}
