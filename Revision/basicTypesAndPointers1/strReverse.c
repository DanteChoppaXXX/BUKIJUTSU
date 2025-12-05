/*
    A Program That Takes A String And Reverses It.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(void)
{
    char str[BUFFER_SIZE];
    char revstr[BUFFER_SIZE];

    printf("Enter any text: ");
    fgets(str, BUFFER_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    printf("You entered => %s\n", str);

    int length = strlen(str);
    for (int i = 0; i < length; i++)
    {
        revstr[i] = str[length - i - 1];
    }

    revstr[length] = '\0';
    printf("Reversed => %s\n", revstr);
    
    return EXIT_SUCCESS;
}
