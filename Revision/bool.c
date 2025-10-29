#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    bool x = true;
    bool y = false;

    printf("x = %d\ny = %d\n", x, y);

    if (x)
    {
        printf("You Are Victorious!\n");
    }
    else 
    {
        printf("Try Again!\n");
    }

    return 0;
}
