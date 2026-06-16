// Write a program that prints the addresses of global, static, local, malloc'd variables and address of function.

#include <stdio.h>
#include <stdlib.h>

int global = 10;
static int static_value = 20;

int add(void)
{
    return 1+1;

}


int main(void)
{
    int local = 30;
    int *ptr = malloc(sizeof(int));
    if (ptr == NULL) {
    
        fprintf(stderr, "Memory Allocation Failed!\n");
    }


    printf("Address of global => %p\n", &global);
    printf("Address of local => %p\n", &local);
    printf("Address of static => %p\n", &static_value);
    printf("Address of malloc'd => %p\n", &ptr);
    printf("Address of function => %p\n", &add);
    printf("Address of function => %p\n", add);

    free(ptr);
    return 0;
}
