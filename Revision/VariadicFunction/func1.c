#include <stdio.h>

void func(int a, ...)
{
    printf("a is %d\n", a);    // prints "a is 2"
}

int main(void)
{
    func(2, 3, 4, 5, 6);
}
