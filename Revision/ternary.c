#include <stdio.h>
#include <stdbool.h>

int main(void)
{

    int x = 15;
    int y = 0;
    printf("x = %d\ny = %d\n", x, y += x > 10? 20: 15);
    printf("The value of x is %d and it's an %s number\n", x, x % 2 == 0? "Even": "Odd");

    return 0;
}
