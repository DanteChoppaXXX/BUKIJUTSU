#include <stdio.h>

enum {
    ONE=1,
    TWO=2
};

// enums are automatically numbered unless you override them. They start at 0, and autoincrement up from there, by default:
enum things {
    SHEEP,
    WHEAT,
    MAN,
    SWORD,
    WOOD
};

typedef enum {
    SHIP,
    MEAT,
    WOMAN,
    MONEY,
    WEAPONS
} RESOURCES;

int main(void)
{
    printf("%d %d\n", ONE, TWO);
    printf("%d %d\n", SHEEP, WHEAT);
    printf("%d %d\n", MAN, SWORD);

    // An array of enum things. 
    enum things t[] = {SHEEP, MAN, WOOD};

    for (int i = 0; i < 3; i++) {
    
        printf("%d\n", t[i]);
    }

    // enum variable.
    RESOURCES r = WEAPONS;

    if (r == WEAPONS) {
    
        printf("I'll trade weapons for money\n");
    }
}
