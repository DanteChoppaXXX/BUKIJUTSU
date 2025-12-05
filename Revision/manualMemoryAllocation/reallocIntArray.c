// Allocate memory for an array of integer, store somethings in there and print them.
// Calloc() is best for array cause it initializes the memory to zero.
// Then reallocate the memory with realloc() increase the size of the array.

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

    // Reallocate the memory to hold 20 integers.
    int *moredigits = realloc(digits, sizeof(int) * 20);

    // Check if reallocation failed.
    if (moredigits == NULL)
    {
        perror("Memory Reallocation Failed!");
        return EXIT_FAILURE;
    }

    // Reassign digits(Original Allocated Memory) with moredigits(Newly Resized Memory).
    digits = moredigits;

    printf("After Reallocation:\n");

    // Store somethings in allocated memory.
    for (int i = 0; i < 20; i++)
    {
        digits[i] = i * 5;
    
    }

    // Print the stored integers.
    digit = digits; 

    for (int i = 0; i < 20; i++)
    {
        printf("Allocated Memory (%p) Holds The Values %d:\n", digit, digits[i]);
        digit++;
    }


    free(digits);

    return EXIT_SUCCESS;
}
