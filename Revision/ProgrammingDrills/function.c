/* Write a function that takes args, calls another function and returns a value. */

#include <stdio.h>
#include <string.h>

int strLength(const char *str0, const char *str1)
{
    // Call strlen() to get the number of characters in the strings.
    return (strlen(str0) + strlen(str1));
}

int main(void)
{
    const char *word0 = "Bicycles";
    const char *word1 = "Skateboards";

    printf("The words has %d characters\n", strLength(word0, word1));

    return 0;
}
