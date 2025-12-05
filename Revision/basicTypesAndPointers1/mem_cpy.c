#include <stdio.h>
#include <stdlib.h>


void *mem_cpy(void *d , void *s, unsigned long size)
{
    // Convert void to char.
    char *dest = d, *src = s;

    // Dereference and copy them (the char).
    while (size--) 
    {
        *dest++ = *src++;
    }
    return dest;
}

int main(void)
{
    char *str = "Hello C!";
    char string[10];

    mem_cpy(string, str, sizeof(string));
    printf("%s\n", string);

    return EXIT_SUCCESS;
}
