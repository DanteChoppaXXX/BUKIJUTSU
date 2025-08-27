/*
    A Simple Timer Program 
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

// Function Prototype.
int get_minutes(const char *string);
void countdown(int *seconds);

int main(int argc, char *argv[])
{
    // Take user input as commandline arguments.
    // check for proper arguments.
    if (argc != 2)
    {
        printf("usage: %s <minutes>"
               "\n[Exiting...]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    // Validate user input is an integer.
    int minutes = get_minutes(argv[1]);
    if (minutes == -1)
    {
        fprintf(stderr, "[x] Invalid Minutes: %s (Enter 1 to 1440)\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    
    // Convert the minutes to seconds.
    int seconds = minutes * 60;

    printf("\033[1;32m[+] Timer Set For %d Minutes [%d Seconds]\n", minutes, seconds);

    // Invoke countdown function.
    countdown(&seconds);

    // Display message upon countdown completion.
    printf("\033[1;31m[-] Time Up! [DONE]\n");


    return EXIT_SUCCESS;
}

// Function to get timer minutes.
int get_minutes(const char *string)
{
    // Ensure only digits.
    for (const char *minutes = string; *minutes; minutes++)
    {
        if (!isdigit((unsigned char)*minutes))
        {
            return -1;
        }
    }
    
    // Convert and check range.
    int minutes = atoi(string);
    return (minutes >= 1 && minutes <= 1440) ? minutes : -1;
}    

// Timer countdown function.
void countdown(int *seconds)
{
    // Initiate countdown with a while loop.
    while (*seconds)
    {
        // Display time left.
        printf("\033[0m[+] Time Left [\033[1;33m%d\033[0m]\n", *seconds);
        printf("\033[A\033[2K");
        // printf("\r%d", seconds);

        // Sleep 1 second.
        sleep(1);

        // Decrease seconds by 1.
        *seconds -= 1;
    }

}
