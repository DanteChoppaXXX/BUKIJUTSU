// Write your own strlen() from memory.

#include <stdio.h>
#include <string.h>

int myStrlen(const char *str)
{
    int count = 0;

    // Assign the str pointer to a pointer in order not to move the orginal pointer.
    const char *string = str;

    while (*string != '\0')
    {
        string++;
        count++;
    }
    return count;
}

int main(void)
{
    char name[255];
    
    printf("Enter any word: ");
    fgets(name, 255, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("The word has %d characters\n", myStrlen(name));
    return 0;
}
