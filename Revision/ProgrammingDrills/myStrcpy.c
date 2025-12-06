// Write your own strcpy() from memory.

#include <stdio.h>
#include <string.h>

int myStrcpy(char *src, char *dest)
{
    char *srcPtr = src;
    char *destPtr = dest;
    int count = 0;

    while (*srcPtr != '\0')
    {
        *destPtr = *srcPtr;       
        count++;
        srcPtr++;
        destPtr++;
    }
    dest[count] = '\0';
    return count;
}

int main(void)
{
    char name[255];
    char newName[255];
    
    printf("Enter any word: ");
    fgets(name, 255, stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Name => %s\n", name);
    printf("Copied %d bytes into destination buffer\n", myStrcpy(name, newName));
    
    printf("New name => %s\n", newName);
    
    return 0;
}
