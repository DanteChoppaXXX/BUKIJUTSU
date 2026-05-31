#include <stddef.h>
#include <stdio.h>

// Size of this struct is 12.
// struct foo {
//     char a;
//     char b;
//     int c;
//     int d;
// };

// Size of this struct is 16.
struct foo {
    char a;
    int b;
    int c;
    char d;
};

int main(void)
{
    printf("%zu\n", sizeof(int) + sizeof(char) + sizeof(int) + sizeof(char));
    printf("%zu\n", sizeof(struct foo));

    printf("\n");
    printf("%zu\n", offsetof(struct foo, a));
    printf("%zu\n", offsetof(struct foo, b));
    printf("%zu\n", offsetof(struct foo, c));
    printf("%zu\n", offsetof(struct foo, d));
}
