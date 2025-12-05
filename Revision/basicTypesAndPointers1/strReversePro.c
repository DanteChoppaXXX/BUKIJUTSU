/*
    A Program That Takes A String And Reverses It In-Place.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char str[BUFFER_SIZE];
    char *start, *end;

    printf("Enter any text: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    printf("You entered => %s\n", str);

    int length = strlen(str);
    start = str;
    end = &str[length - 1];
    start = end;
    end = start;

    printf("Reversed => %c\n", *start);
    printf("Reversed => %c\n", *end);
    for (int i = 0; i < length; i++)
    {
                start++;
        end--;
    }

    str[length] = '\0';
    printf("Reversed => %s\n", str);
    
    return EXIT_SUCCESS;
}

