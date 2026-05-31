#include <stdio.h>

struct parent {
    int a, b;
};

struct child {
    struct parent super;        // MUST BE FIRST
    int c, d;
};

// Making  the argument "void*" so we can pass any type into it (namely a struct parent or struct child)
void print_parent(void *p)
{
    // Expects a struct parent -- but a struct child will also work because the pointer points to the struct parent in the first field:
    struct parent *self = p;

    printf("Parent: %d, %d\n", self->a, self->b);
}

void print_child(struct child *self)
{
    printf("Child: %d, %d\n", self->c, self->d);
}

int main(void)
{
    struct child c = {.super.a=1, .super.b=2, .c=3, .d=4};

    print_child(&c);
    print_parent(&c);        // Also works even though it's a struct child!
}
