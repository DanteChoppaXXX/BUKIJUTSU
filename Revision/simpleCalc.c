/*
    A Simple Calculator Program.
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("[Usage: Enter first number\nthen an arithmetic operator[+, -, /, "
           "*]\nthen the second number\nfinally hit enter for the result]\n");

    float x, y, result;
    char op;

    while (1)
    {
        printf("\033[1m> ");
        scanf("%f", &x);
        scanf("%c", &op);
        scanf("%f", &y);

        switch (op)
        {
        case '+':
            result = x + y;
            break;

        case '-':
            result = x - y;
            break;

        case '/':
            result = x / y;
            break;

        case '*':
            result = x * y;
            break;
        default:
            result = x / y;
            break;
        }

        printf("\033[32m= %f\033[0m\n", result);
    }

    return EXIT_SUCCESS;
}
