// Implement an Array-based stack.

#include <stdio.h>
#include <stdlib.h>

#define MAX 5

// Global variables
int stack_arr[MAX];
int top = -1;

// Function prototype.
void push(int value);
int pop();
void print();
int isFull();
int isEmpty();
int peek();

int main(void)
{
    // Ask the user what they want to do.
    int choice;
    int value;
    while (1) {
    
        printf("\n1. Push\n2. Pop\n3. Print the top element\n4. Print all elements\n5. Quit\n\nPlease enter your choice(1, 2, 3, 4, 5): ");
        scanf("%d%*c", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to push onto the stack: ");
                scanf("%d%*c", &value);
                push(value);
                isFull() ? printf("\n[!] Stack Is Now Full! [WARNING]\n") : printf("\n") ;                
                break;
            case 2:
                value = pop();
                printf("\n[+] Popped %d from the stack [SUCCESS]\n", value);
                break;
            case 3:
                printf("\n[+] Top Element => [%d]\n", peek());
                break;
            case 4:
                print();
                break;
            case 5:
                return 0;
            default:
                break;
        }
    
    }
    return 0;
}

void push(int value)
{
    // Check if stack is full.
    if (isFull()) {
        printf("[x] Stack Overflow! [FAILED]\n");
        return;
    }
    // increment top by 1.
    top += 1;
    // Add value to the stack array.
    stack_arr[top] = value;
    printf("\n[+] Pushed %d onto the stack [SUCCESS]\n", value);
}

int pop()
{
    // Check if stack is empty.
    if (isEmpty()) {
        printf("[x] Stack Underflow! [FAILED]\n");
        exit(1);
    }
    // Store the element in variable.
    int value = stack_arr[top];
    
    // Decrement top by 1.
    top -= 1;

    return value;
}

void print()
{
    // Check if stack is empty.
    if (isEmpty()) {
        printf("[x] Stack Underflow! [FAILED]\n");
        exit(1);
    }

    printf("\nElements on the stack:\n");
    for (int i = top; i >= 0; i--) {
        printf("%d. %d\n", i + 1, stack_arr[i]);
    }

}

int isFull()
{
    if (top == MAX - 1) {
        return 1;
    }
    else {
        return 0;
    }
}

int isEmpty()
{
    if (top == -1) {
        return 1;
    }
    else {
        return 0;
    }
}

int peek()
{
    // Check if stack is empty.
    if (isEmpty()) {
        printf("[x] Stack Underflow! [FAILED]\n");
        exit(1);
    }

    return stack_arr[top];

}
