// Implement : Dynamic array using malloc + free.

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int size;
    // Get the size of array from the user.
    printf("Enter the amount of numbers: ");
    scanf("%d", &size);

    if (size <= 0)
    {
        printf("Size must be positive.\n");
        return 1;
    }

    int *numbers = malloc(size * sizeof(int));
    if (numbers == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Get the numbers from the user.
    size > 1 ? printf("Enter all %d numbers: ", size) : printf("Enter the number: ");

    for (int i = 0; i < size; i++) 
    {
        scanf("%d", &numbers[i]);
    }
    
    printf("You entered: \n");
    for (int i = 0; i < size; i++) 
    {
        printf("%d\n", numbers[i]);
    }
    
    int sum = 0;
    
    for (int i = 0; i < size; i++) 
    {
        sum += numbers[i];
    }

    printf("\nThe Average of the numbers is => [%.2f]\n", (float)sum / size);
    
    free(numbers);

    return 0;
}
